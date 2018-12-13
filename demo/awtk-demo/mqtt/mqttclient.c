/*****************************Copyright(c)*************************************
** 							  By zhaoqi.
**
**                            http://blog.zhaoqi.info
**
**------File Info--------------------------------------------------------------
** File Name:              mqttclient.c
** Latest modified Date:   2018-6-6
** Latest Version:         V1.0
** Description:            mqtt客户端封装
**
**-----------------------------------------------------------------------------
** Created By:             zhaoqi
** Created date:           2018-6-6
** Version:                V1.0
** Descriptions:           mqtt客户端封装
**
**-----------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Description:
**
******************************************************************************/

#include "mqttclient.h"



/**
 * @brief 初始化客户端并登录服务器
 */
int8_t MQTTClientInit(__mqtt_handle_t *mqtt_handle)
{
//    MQTTPacket_connectData connectData = MQTTPacket_connectData_initializer;
    uint8_t buf[128];
    uint32_t buflen = sizeof(buf);
    uint16_t len;
    uint8_t sessionPresent, connack_rc;
    uint16_t time_out = 100;

    //创建MQTT客户端连接参数
//    connectData.willFlag = 0;
//    //MQTT版本
//    connectData.MQTTVersion = 4;
//    //客户端ID--必须唯一
//    connectData.clientID.cstring = "MIMITOTO";
//    //保活间隔
//    connectData.keepAliveInterval = 60;
//    //用户名
//    connectData.username.cstring = "zq";
//    //用户密码
//    connectData.password.cstring = "zhaoqi";
//    //清除会话
//    connectData.cleansession = 1;

    //串行化连接消息
    len = MQTTSerialize_connect(buf, buflen, &(mqtt_handle->connectData));
    //发送TCP数据

    if ((*mqtt_handle->fpn_send)(buf, len) < 0) {
        return -1;
    }


    fd_set readfd;
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    //推送消息
    FD_ZERO(&readfd);
    FD_SET(mqtt_handle->socket,&readfd);

    select(mqtt_handle->socket+1,&readfd,NULL,NULL,&tv);
    if(FD_ISSET(mqtt_handle->socket,&readfd) == 0) {
        return -2;
    }
    if(MQTTPacket_read(buf, buflen, mqtt_handle->fpn_recv) != CONNACK)
        return -4;
    //拆解连接回应包
    if (MQTTDeserialize_connack(&sessionPresent, &connack_rc, buf, buflen) != 1 || connack_rc != 0)
        return -5;

    if (sessionPresent == 1) {
        return 1;//不需要重新订阅--服务器已经记住了客户端的状态
    } else {
        return 0;//需要重新订阅
    }
}

/**
 * @brief 客户端订阅主题
 */
int8_t MQTTSubscribe(__mqtt_handle_t *mqtt_handle, uint8_t *topic, enum QoS pos)
{
    static uint16_t PacketID = 0;
    uint16_t packetidbk = 0;
    int conutbk = 0;
    uint8_t buf[200];
    uint16_t buflen = sizeof(buf);
    MQTTString topicString = MQTTString_initializer;
    uint16_t len;
    int req_qos, qosbk;
    uint8_t time_out = 200;


    //复制主题
    topicString.cstring = (char *)topic;
    //订阅质量
    req_qos = pos;

    //串行化订阅消息
    len = MQTTSerialize_subscribe(buf, buflen, 0, PacketID++, 1, &topicString, &req_qos);
    //发送TCP数据
    if ((*mqtt_handle->fpn_send)(buf, len) < 0) {
        return -1;
    }

    fd_set readfd;
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    //推送消息
    FD_ZERO(&readfd);
    FD_SET(mqtt_handle->socket,&readfd);

    select(mqtt_handle->socket+1,&readfd,NULL,NULL,&tv);
    if(FD_ISSET(mqtt_handle->socket,&readfd) == 0) {
        return -2;
    }

    //等待订阅返回--未收到订阅返回
    if(MQTTPacket_read(buf, buflen, mqtt_handle->fpn_recv) != SUBACK) {
        return -4;
    }


    //拆订阅回应包
    if(MQTTDeserialize_suback(&packetidbk, 1, &conutbk, &qosbk, buf, buflen) != 1) {
        return -5;
    }


    //检测返回数据的正确性
    if((qosbk == 0x80) || (packetidbk != (PacketID - 1))) {
        return -6;
    }
    //订阅成功
    return 0;
}

/**
 * @brief 阻塞读取MQTT数据
 */
int32_t ReadPacketTimeout(__mqtt_handle_t *mqtt_handle, uint8_t *buf, int32_t buflen, uint32_t timeout)
{

    fd_set readfd;
    struct timeval tv;
    tv.tv_sec = timeout/1000;
    tv.tv_usec = (timeout%1000) * 1000;
    //推送消息
    FD_ZERO(&readfd);
    FD_SET(mqtt_handle->socket,&readfd);

    select(mqtt_handle->socket+1,&readfd,NULL,NULL,&tv);
    if(FD_ISSET(mqtt_handle->socket,&readfd) == 0) {
        return -1;
    }

    return MQTTPacket_read(buf, buflen, mqtt_handle->fpn_recv);
    //读取TCP/IP事件

}

/**
 * @brief 等待特定的数据包
 */
int32_t WaitForPacket(__mqtt_handle_t *mqtt_handle, uint8_t packettype, uint8_t times)
{
    int32_t type;
    uint8_t buf[256];
    uint8_t n = 0;
    int32_t buflen = sizeof(buf);
    do
    {
        //读取数据包
        type = ReadPacketTimeout(mqtt_handle, buf, buflen, 2);
        if(type != -1) {
            mqtt_pktype_ctl(mqtt_handle,type, buf, buflen);
        }
        n++;
    } while((type != packettype) && (n < times));
    //收到期望的包
    if (type == packettype) {
        return 0;
    }
    return -1;
}

/**
 * @brief 用户推送消息
 */
int32_t MQTTMsgPublish(__mqtt_handle_t *mqtt_handle, 
                        uint8_t *topic, 
                        uint8_t qos, 
                        uint8_t retained, 
                        uint8_t* msg,
                        uint32_t msg_len)
{
    static uint8_t buf[3072] = {0,};
    static uint16_t qospackid = 0;
    uint32_t buflen = sizeof(buf), len;
    MQTTString topicString = MQTTString_initializer;
    uint16_t packid = 0, packetidbk;

    /* 填充主题 */
    topicString.cstring = (char *)topic;

    /* 填充数据包ID */
    if ((qos == QOS1) || (qos == QOS2)) {
        //packid = GetNextPackID();
        packid = qospackid++;
    } else {
        qos = QOS0;
        retained = 0;
        packid = 0;
    }

    /* 推送消息 */
    len = MQTTSerialize_publish(buf, buflen, 0, qos, retained, packid, topicString, (unsigned char*)msg, msg_len);
    if (len <= 0) {
        return -1;
    }
    if ((*mqtt_handle->fpn_send)(buf, len) < 0) {
        return -2;
    }

    /* 质量等级0，不需要返回 */
    if (qos == QOS0) {
        return 0;
    }

    /* 等级1 */
    if (qos == QOS1) {
        /* 等待PUBACK */
        if(WaitForPacket(mqtt_handle, PUBACK, 5) < 0)
            return -3;
        return 1;

    }

    /* 等级2 */
    if (qos == QOS2) {
        /* 等待PUBREC */
        if(WaitForPacket(mqtt_handle, PUBREC, 5) < 0)
            return -3;
        /* 发送PUBREL */
        len = MQTTSerialize_pubrel(buf, buflen, 0, packetidbk);
        if(len == 0)
            return -4;
        if((*mqtt_handle->fpn_send)(buf, len) < 0)
            return -6;
        /* 等待PUBCOMP */
        if(WaitForPacket(mqtt_handle, PUBREC, 5) < 0)
            return -7;
        return 2;
    }
    
    /* 等级错误 */
    return -8;
}

/**
 * @brief 客户端PING请求
 */
int8_t MQTTPingreq(__mqtt_handle_t *mqtt_handle)
{
    uint16_t len;
    uint8_t buf[256];
    uint16_t buflen = sizeof(buf);
    uint8_t time_out = 200;

    
    len = MQTTSerialize_pingreq(buf, buflen);
    if ((*mqtt_handle->fpn_send)(buf, len) < 0) {
        return -1;
    }

    fd_set readfd;
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;

    FD_ZERO(&readfd);
    FD_SET(mqtt_handle->socket,&readfd);

    select(mqtt_handle->socket+1,&readfd,NULL,NULL,&tv);
    if(FD_ISSET(mqtt_handle->socket,&readfd) == 0) {
        return -2;
    }

    if(MQTTPacket_read(buf, buflen, mqtt_handle->fpn_recv) != PINGRESP) {
        return -3;
    }
    return 0;
}

/**
 * @brief 根据包类型进行处理
 */
void mqtt_pktype_ctl(__mqtt_handle_t *mqtt_handle, 
                        uint8_t packtype, 
                        uint8_t *buf, 
                        uint16_t buflen)
{
    uint8_t dup = 0;
    uint32_t qos = 0;
    uint8_t retained = 0;
    uint16_t id = 0;
    uint8_t *payload = NULL;
    uint16_t payloadlen = 0;
    uint8_t type = 0;
    int32_t rc;
    MQTTString receivedTopic;
    int32_t len;
    switch (packtype) {
        
    case PUBLISH:
        /* 拆析PUBLISH消息 */
        if(MQTTDeserialize_publish(&dup, (int*)&qos, &retained, &id, &receivedTopic, (unsigned char **)&payload, (int *)&payloadlen, buf, buflen) != 1)
            return;

        /* 接受消息 */
        /* 消息质量不同，处理不同 */
        if (qos == QOS0) {
            /* QOS0-不需要ACK
               直接处理数据      
            */
            if (mqtt_handle->fpn_on_sub_rec != NULL) {
                (*mqtt_handle->fpn_on_sub_rec)(&receivedTopic, payload, payloadlen);
            }
            return ;
        }
        
        /* 发送PUBACK消息 */
        if (qos == QOS1) {
            len = MQTTSerialize_puback(buf, buflen, id);
            if (len == 0) {
                return;
            }       

            /* 发送返回 */
            if ((*mqtt_handle->fpn_send)(buf, len) < 0) {
                return ;
            }
            return;
        }

        /* 对于质量2,只需要发送PUBREC就可以了 */
        if (qos == QOS2) {
            len = MQTTSerialize_ack(buf, buflen, PUBREC, 0, id);
            if(len == 0)
                return;
            /* 发送返回 */
            if ((*mqtt_handle->fpn_send)(buf, len) < 0) {
                return ;
            }
        }
        break;
        
    case  PUBREL:
        /* 解析包数据，必须包ID相同才可以 */
        rc = MQTTDeserialize_ack(&type, &dup, &id, buf, buflen);
        if ((rc != 1) || (type != PUBREL) ) {
            return ;
        } 
        /* 串行化PUBCMP消息 */
        len = MQTTSerialize_pubcomp(buf, buflen, id);
        if(len == 0) {
            return;
        }      
        /* 发送返回--PUBCOMP */
        if ((*mqtt_handle->fpn_send)(buf, len) < 0) {
            return ;
        }
        break;
    case   PUBACK:  /* 等级1客户端推送数据后，服务器返回 */
        break;
    
    case   PUBREC:  /* 等级2客户端推送数据后，服务器返回 */
        break;
    
    case   PUBCOMP: /* 等级2客户端推送PUBREL后，服务器返回 */
        break;
    
    default:
        break;
    }
}

