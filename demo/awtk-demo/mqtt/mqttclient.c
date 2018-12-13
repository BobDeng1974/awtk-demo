/*****************************Copyright(c)*************************************
** 							  By zhaoqi.
**
**                            http://blog.zhaoqi.info
**
**------File Info--------------------------------------------------------------
** File Name:              mqttclient.c
** Latest modified Date:   2018-6-6
** Latest Version:         V1.0
** Description:            mqtt�ͻ��˷�װ
**
**-----------------------------------------------------------------------------
** Created By:             zhaoqi
** Created date:           2018-6-6
** Version:                V1.0
** Descriptions:           mqtt�ͻ��˷�װ
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
 * @brief ��ʼ���ͻ��˲���¼������
 */
int8_t MQTTClientInit(__mqtt_handle_t *mqtt_handle)
{
//    MQTTPacket_connectData connectData = MQTTPacket_connectData_initializer;
    uint8_t buf[128];
    uint32_t buflen = sizeof(buf);
    uint16_t len;
    uint8_t sessionPresent, connack_rc;
    uint16_t time_out = 100;

    //����MQTT�ͻ������Ӳ���
//    connectData.willFlag = 0;
//    //MQTT�汾
//    connectData.MQTTVersion = 4;
//    //�ͻ���ID--����Ψһ
//    connectData.clientID.cstring = "MIMITOTO";
//    //������
//    connectData.keepAliveInterval = 60;
//    //�û���
//    connectData.username.cstring = "zq";
//    //�û�����
//    connectData.password.cstring = "zhaoqi";
//    //����Ự
//    connectData.cleansession = 1;

    //���л�������Ϣ
    len = MQTTSerialize_connect(buf, buflen, &(mqtt_handle->connectData));
    //����TCP����

    if ((*mqtt_handle->fpn_send)(buf, len) < 0) {
        return -1;
    }


    fd_set readfd;
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    //������Ϣ
    FD_ZERO(&readfd);
    FD_SET(mqtt_handle->socket,&readfd);

    select(mqtt_handle->socket+1,&readfd,NULL,NULL,&tv);
    if(FD_ISSET(mqtt_handle->socket,&readfd) == 0) {
        return -2;
    }
    if(MQTTPacket_read(buf, buflen, mqtt_handle->fpn_recv) != CONNACK)
        return -4;
    //������ӻ�Ӧ��
    if (MQTTDeserialize_connack(&sessionPresent, &connack_rc, buf, buflen) != 1 || connack_rc != 0)
        return -5;

    if (sessionPresent == 1) {
        return 1;//����Ҫ���¶���--�������Ѿ���ס�˿ͻ��˵�״̬
    } else {
        return 0;//��Ҫ���¶���
    }
}

/**
 * @brief �ͻ��˶�������
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


    //��������
    topicString.cstring = (char *)topic;
    //��������
    req_qos = pos;

    //���л�������Ϣ
    len = MQTTSerialize_subscribe(buf, buflen, 0, PacketID++, 1, &topicString, &req_qos);
    //����TCP����
    if ((*mqtt_handle->fpn_send)(buf, len) < 0) {
        return -1;
    }

    fd_set readfd;
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    //������Ϣ
    FD_ZERO(&readfd);
    FD_SET(mqtt_handle->socket,&readfd);

    select(mqtt_handle->socket+1,&readfd,NULL,NULL,&tv);
    if(FD_ISSET(mqtt_handle->socket,&readfd) == 0) {
        return -2;
    }

    //�ȴ����ķ���--δ�յ����ķ���
    if(MQTTPacket_read(buf, buflen, mqtt_handle->fpn_recv) != SUBACK) {
        return -4;
    }


    //���Ļ�Ӧ��
    if(MQTTDeserialize_suback(&packetidbk, 1, &conutbk, &qosbk, buf, buflen) != 1) {
        return -5;
    }


    //��ⷵ�����ݵ���ȷ��
    if((qosbk == 0x80) || (packetidbk != (PacketID - 1))) {
        return -6;
    }
    //���ĳɹ�
    return 0;
}

/**
 * @brief ������ȡMQTT����
 */
int32_t ReadPacketTimeout(__mqtt_handle_t *mqtt_handle, uint8_t *buf, int32_t buflen, uint32_t timeout)
{

    fd_set readfd;
    struct timeval tv;
    tv.tv_sec = timeout/1000;
    tv.tv_usec = (timeout%1000) * 1000;
    //������Ϣ
    FD_ZERO(&readfd);
    FD_SET(mqtt_handle->socket,&readfd);

    select(mqtt_handle->socket+1,&readfd,NULL,NULL,&tv);
    if(FD_ISSET(mqtt_handle->socket,&readfd) == 0) {
        return -1;
    }

    return MQTTPacket_read(buf, buflen, mqtt_handle->fpn_recv);
    //��ȡTCP/IP�¼�

}

/**
 * @brief �ȴ��ض������ݰ�
 */
int32_t WaitForPacket(__mqtt_handle_t *mqtt_handle, uint8_t packettype, uint8_t times)
{
    int32_t type;
    uint8_t buf[256];
    uint8_t n = 0;
    int32_t buflen = sizeof(buf);
    do
    {
        //��ȡ���ݰ�
        type = ReadPacketTimeout(mqtt_handle, buf, buflen, 2);
        if(type != -1) {
            mqtt_pktype_ctl(mqtt_handle,type, buf, buflen);
        }
        n++;
    } while((type != packettype) && (n < times));
    //�յ������İ�
    if (type == packettype) {
        return 0;
    }
    return -1;
}

/**
 * @brief �û�������Ϣ
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

    /* ������� */
    topicString.cstring = (char *)topic;

    /* ������ݰ�ID */
    if ((qos == QOS1) || (qos == QOS2)) {
        //packid = GetNextPackID();
        packid = qospackid++;
    } else {
        qos = QOS0;
        retained = 0;
        packid = 0;
    }

    /* ������Ϣ */
    len = MQTTSerialize_publish(buf, buflen, 0, qos, retained, packid, topicString, (unsigned char*)msg, msg_len);
    if (len <= 0) {
        return -1;
    }
    if ((*mqtt_handle->fpn_send)(buf, len) < 0) {
        return -2;
    }

    /* �����ȼ�0������Ҫ���� */
    if (qos == QOS0) {
        return 0;
    }

    /* �ȼ�1 */
    if (qos == QOS1) {
        /* �ȴ�PUBACK */
        if(WaitForPacket(mqtt_handle, PUBACK, 5) < 0)
            return -3;
        return 1;

    }

    /* �ȼ�2 */
    if (qos == QOS2) {
        /* �ȴ�PUBREC */
        if(WaitForPacket(mqtt_handle, PUBREC, 5) < 0)
            return -3;
        /* ����PUBREL */
        len = MQTTSerialize_pubrel(buf, buflen, 0, packetidbk);
        if(len == 0)
            return -4;
        if((*mqtt_handle->fpn_send)(buf, len) < 0)
            return -6;
        /* �ȴ�PUBCOMP */
        if(WaitForPacket(mqtt_handle, PUBREC, 5) < 0)
            return -7;
        return 2;
    }
    
    /* �ȼ����� */
    return -8;
}

/**
 * @brief �ͻ���PING����
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
 * @brief ���ݰ����ͽ��д���
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
        /* ����PUBLISH��Ϣ */
        if(MQTTDeserialize_publish(&dup, (int*)&qos, &retained, &id, &receivedTopic, (unsigned char **)&payload, (int *)&payloadlen, buf, buflen) != 1)
            return;

        /* ������Ϣ */
        /* ��Ϣ������ͬ������ͬ */
        if (qos == QOS0) {
            /* QOS0-����ҪACK
               ֱ�Ӵ�������      
            */
            if (mqtt_handle->fpn_on_sub_rec != NULL) {
                (*mqtt_handle->fpn_on_sub_rec)(&receivedTopic, payload, payloadlen);
            }
            return ;
        }
        
        /* ����PUBACK��Ϣ */
        if (qos == QOS1) {
            len = MQTTSerialize_puback(buf, buflen, id);
            if (len == 0) {
                return;
            }       

            /* ���ͷ��� */
            if ((*mqtt_handle->fpn_send)(buf, len) < 0) {
                return ;
            }
            return;
        }

        /* ��������2,ֻ��Ҫ����PUBREC�Ϳ����� */
        if (qos == QOS2) {
            len = MQTTSerialize_ack(buf, buflen, PUBREC, 0, id);
            if(len == 0)
                return;
            /* ���ͷ��� */
            if ((*mqtt_handle->fpn_send)(buf, len) < 0) {
                return ;
            }
        }
        break;
        
    case  PUBREL:
        /* ���������ݣ������ID��ͬ�ſ��� */
        rc = MQTTDeserialize_ack(&type, &dup, &id, buf, buflen);
        if ((rc != 1) || (type != PUBREL) ) {
            return ;
        } 
        /* ���л�PUBCMP��Ϣ */
        len = MQTTSerialize_pubcomp(buf, buflen, id);
        if(len == 0) {
            return;
        }      
        /* ���ͷ���--PUBCOMP */
        if ((*mqtt_handle->fpn_send)(buf, len) < 0) {
            return ;
        }
        break;
    case   PUBACK:  /* �ȼ�1�ͻ����������ݺ󣬷��������� */
        break;
    
    case   PUBREC:  /* �ȼ�2�ͻ����������ݺ󣬷��������� */
        break;
    
    case   PUBCOMP: /* �ȼ�2�ͻ�������PUBREL�󣬷��������� */
        break;
    
    default:
        break;
    }
}

