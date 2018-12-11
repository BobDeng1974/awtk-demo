    
    <view w="100%" h="100%" layout="r1 c0 m20" >
      <list_view name="qq_msg" x="40"  y="10" w="100%" h="-80" item_height="70">
        <scroll_view name="qq_view" x="0"  y="0" w="100%" h="100%">
          <list_item style="odd_clickable" y="t:5" h="50" layout="r1 c0 s2 m2">
            <image draw_type="icon" y="t" w="60" image="a"/>
            <label style="qq_main_black" x="r:10" w="-60" text="AWTK使用交流">
              <view x="r:5" y="m" w="60" h="50">
                <label style="qq_black" x="r:10" y="t:-10" w="60" h="20" text="15:35" />
                <label style="qq_black" x="r:600" y="m" w="60" h="20" text="您有一条新消息!" />
                <image draw_type="icon" x="r:30" y="b:3" w="60" h="20" image="red_circle"/>
                <label style="qq_num_index" x="r:30" y="m:11" w="60" h="20" text="3" />    
              </view>
            </label>
          </list_item>
          <list_item style="odd_clickable" y="t:5" h="50" layout="r1 c0 s2 m2">
            <image draw_type="icon" y="t" w="60" image="a"/>
            <label style="qq_main_black" x="r:10" w="-60" text="致远QQ群">
              <view x="r:5" y="m" w="60" h="50">
                <label style="qq_black" x="r:10" y="t:-10" w="60" h="20" text="15:35" />
                <label style="qq_black" x="r:600" y="m" w="60" h="20" text="大家好啊!" />
                <image draw_type="icon" x="r:30" y="b:3" w="60" h="20" image="red_circle"/>
                <label style="qq_num_index" x="r:30" y="m:11" w="60" h="20" text="1" />    
              </view>
            </label>
          </list_item>
        </scroll_view>
        <scroll_bar_m name="bar" x="right" y="0" w="6" h="100%" value="0"/>
      </list_view>

    </view>
