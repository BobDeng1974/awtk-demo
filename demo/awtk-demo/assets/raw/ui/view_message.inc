    
    <view w="100%" h="100%" layout="r1 c0 m20" >
      <list_view name="qq_msg" x="40"  y="10" w="100%" h="-80" item_height="70">
        <scroll_view name="qq_view" x="0"  y="0" w="100%" h="100%">
          <list_item style="odd_clickable" y="5" h="50" layout="r1 c0 s2 m2">
            <view x="5" y="0" w="8%" h="50">
              <image draw_type="icon" x="r:5" y="0" w="100%" h="50" image="a"/>
            </view>
            <view x="r:10" w="82%">
              <label style="qq_main_black" x="r:5" y="m" w="100%" h="50" text="AWTK使用交流" />
              <label style="qq_black" x="r:5" y="m:13" w="100%" h="20" text="您有一条新消息!" />
            </view>
            <view x="r:10" w="10%">
              <label style="qq_black" x="r:10" y="m:-13" w="60" h="20" text="15:35" />
              <image draw_type="icon" x="r:10" y="m:11" w="60" h="20" image="red_circle"/>
              <label style="qq_num_index" x="r:10" y="m:11" w="60" h="20" text="3" />   
            </view>
          </list_item>
          <list_item style="odd_clickable" y="5" h="50" layout="r1 c0 s2 m2">
            <view x="r:5" y="0" w="8%" h="50">
              <image draw_type="icon" x="r:5" y="0" w="100%" h="50" image="a"/>
            </view>
            <view x="r:10" w="82%">
              <label style="qq_main_black" x="r:5" y="m" w="100%" h="50" text="致远QQ群" />
              <label style="qq_black" x="r:5" y="m:13" w="100%" h="20" text="大家好啊!" />
            </view>
            <view x="r:10" w="10%">
              <label style="qq_black" x="r:10" y="m:-13" w="60" h="20" text="15:35" />
              <image draw_type="icon" x="r:10" y="m:11" w="60" h="20" image="red_circle"/>
              <label style="qq_num_index" x="r:10" y="m:11" w="60" h="20" text="1" />   
            </view>
          </list_item>
        </scroll_view>
        <scroll_bar_m name="bar" x="right" y="0" w="6" h="100%" value="0"/>
      </list_view>

    </view>
