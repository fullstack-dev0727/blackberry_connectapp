import bb.cascades 1.4
import "../custom"

Container {
    property int selectedIndex: 0;
    property alias textTab1: label1.text;
    property alias textTab2: label2.text;
    property alias textTab3: label3.text;


    function setSelectedIndex(index) {
        switch (index) {
            case 0 : btTab1Clicked(); return;
            case 1 : btTab2Clicked(); return;
            case 2 : btTab3Clicked(); return;
            case 3 : btTab1Clicked(true); return; //it is used to refresh
        }
        btTab1.clicked();
    }
    
    function btTab1Clicked(forceUpdate) {
        if(selectedIndex != 0 || forceUpdate)
        {
            selectedIndex = 99;
            selectedIndex = 0;
            
            //bottom bar
            backgTab1.background = Color.create("#2d85c2") //blue
            backgTab2.background = Color.create("#fbfbfb") // background gray
            backgTab3.background = Color.create("#fbfbfb") // background gray
            
            //background
            tab1.background = Color.White //blue
            tab2.background = Color.create("#fbfbfb") // background gray
            tab3.background = Color.create("#fbfbfb") // background gray
            
            
            //Tabs layout logic
            label1.textStyle.color = Color.create("#36474f") //deep blue
            label2.textStyle.color = Color.create("#8fa3ad"); //DARKGRAY
            label3.textStyle.color = Color.create("#8fa3ad"); //DARKGRAY
        }
    }
        
  function btTab2Clicked() {
      if(selectedIndex != 1)
      {
          selectedIndex = 1;
          
          //bottom bar
          backgTab1.background = Color.create("#fbfbfb") // background gray
          backgTab2.background = Color.create("#2d85c2") //blue
          backgTab3.background = Color.create("#fbfbfb") // background gray
          
          //background
          tab2.background = Color.White
          tab1.background = Color.create("#fbfbfb") // background gray
          tab3.background = Color.create("#fbfbfb") // background gray

          label2.textStyle.color = Color.create("#36474f"); //deep blue
          label1.textStyle.color = Color.create("#8fa3ad"); //DARKGRAY
          label3.textStyle.color = Color.create("#8fa3ad"); //DARKGRAY
      }
  }
     
 function btTab3Clicked() {
     if(selectedIndex != 2)
     {
         selectedIndex = 2;
         
         //bottom bar
         backgTab1.background = Color.create("#fbfbfb") // background gray
         backgTab2.background = Color.create("#fbfbfb") // background gray
         backgTab3.background = Color.create("#2d85c2") //blue
         
         //background
         tab3.background = Color.White
         tab2.background = Color.create("#fbfbfb") // background gray
         tab1.background = Color.create("#fbfbfb") // background gray

         label3.textStyle.color = Color.create("#36474f"); //deep blue
         label1.textStyle.color = Color.create("#8fa3ad"); //DARKGRAY
         label2.textStyle.color = Color.create("#8fa3ad"); //DARKGRAY
     }
 }

    
    background:  Color.create("#fbfbfb");
    horizontalAlignment: HorizontalAlignment.Fill
    verticalAlignment: VerticalAlignment.Top
    layout: GridLayout {
        columnCount: 3
    }


    Container {
        background: Color.Gray
        
        horizontalAlignment: HorizontalAlignment.Fill
        verticalAlignment: VerticalAlignment.Center

        onTouch: {
            _control.onTouchFunc();
        }
        layout: DockLayout {
        }
    
        Container {
            id: backgTab1
            background: Color.create("#2d85c2");
            
            horizontalAlignment: HorizontalAlignment.Fill
            verticalAlignment: VerticalAlignment.Center
            
            margin.bottomOffset: ui.sdu(0.1)
            margin.topOffset: ui.sdu(0.1)
            margin.rightOffset: ui.sdu(0.1)

                        
            layout: DockLayout {
            }
            
            Container {
                id: tab1
                background: Color.White // white for selected
                topPadding: ui.du(1.5)
                bottomPadding: ui.du(1.5)
                horizontalAlignment: HorizontalAlignment.Fill
                verticalAlignment: VerticalAlignment.Top
                margin.bottomOffset: ui.sdu(0.5)
                
                layout: DockLayout {
                }
                
                ConnectLabel {
                    id: label1
                    horizontalAlignment: HorizontalAlignment.Center
                    verticalAlignment: VerticalAlignment.Center
                    text: ""
                    textStyle.fontSize: FontSize.Small
                    textStyle.fontWeight: FontWeight.W600
                    textStyle.color: Color.create("#36474f")
                }
                Button {
                    id: btTab1
                    horizontalAlignment: HorizontalAlignment.Center
                    verticalAlignment: VerticalAlignment.Center
                    text: ""
                    opacity: 0.01
                    onClicked: {
                        btTab1Clicked(false);
                    }//END ONCLICKED
                }//END BUTTON
            }//END TAB1 CONTAINER
        }
    }
    
    Container {
        background: Color.Gray
        
        horizontalAlignment: HorizontalAlignment.Fill
        verticalAlignment: VerticalAlignment.Center
        
        
        layout: DockLayout {
        }
        
        Container {
            id: backgTab2
            background: Color.create("#fbfbfb") // background gray
            
            horizontalAlignment: HorizontalAlignment.Fill
            verticalAlignment: VerticalAlignment.Center
            
            margin.bottomOffset: ui.sdu(0.1)
            margin.topOffset: ui.sdu(0.1)
            margin.rightOffset: ui.sdu(0.1)

                    
            layout: DockLayout {
            }
            
            Container {
                id: tab2
                background: Color.create("#fbfbfb") // background gray
                topPadding: ui.du(1.5)
                bottomPadding: ui.du(1.5)
                horizontalAlignment: HorizontalAlignment.Fill
                verticalAlignment: VerticalAlignment.Top
                margin.bottomOffset: ui.sdu(0.5)
                
                layout: DockLayout {
                }
                
                
                ConnectLabel {
                    id: label2
                    horizontalAlignment: HorizontalAlignment.Center
                    verticalAlignment: VerticalAlignment.Center
                    text: ""
                    textStyle.fontWeight: FontWeight.W600
                    textStyle.fontSize: FontSize.Small
                    textStyle.color: Color.create("#8fa3ad")
                }
                Button {
                    horizontalAlignment: HorizontalAlignment.Center
                    verticalAlignment: VerticalAlignment.Center
                    text: ""
                    opacity: 0.01
                    onClicked: {
                        btTab2Clicked();
                    }//END ONCLICKED
                }//END BUTTON
            }//END TAB2 CONTAINER
        }    
    }
    
    Container {
        background: Color.Gray
        
        horizontalAlignment: HorizontalAlignment.Fill
        verticalAlignment: VerticalAlignment.Center
        
        
        layout: DockLayout {
        }
        
        Container {
            id: backgTab3
            background: Color.create("#fbfbfb") // background gray
            
            horizontalAlignment: HorizontalAlignment.Fill
            verticalAlignment: VerticalAlignment.Center
            
            margin.bottomOffset: ui.sdu(0.1)
            margin.topOffset: ui.sdu(0.1)
            margin.rightOffset: ui.sdu(0.1)
            
            layout: DockLayout {
            }
                
            Container {
                id: tab3
                background: Color.create("#fbfbfb") // background gray
                topPadding: ui.du(1.5)
                bottomPadding: ui.du(1.5)
                horizontalAlignment: HorizontalAlignment.Fill
                verticalAlignment: VerticalAlignment.Top
                margin.bottomOffset: ui.sdu(0.5)
                
                layout: DockLayout {
                }
                
                
                
                ConnectLabel {
                    id: label3
                    horizontalAlignment: HorizontalAlignment.Center
                    verticalAlignment: VerticalAlignment.Center
                    text: ""
                    textStyle.fontWeight: FontWeight.W600
                    textStyle.fontSize: FontSize.Small
                    textStyle.color: Color.create("#8fa3ad")
                }
                Button {
                    horizontalAlignment: HorizontalAlignment.Center
                    verticalAlignment: VerticalAlignment.Center
                    text: ""
                    opacity: 0.01
                    onClicked: {
                        btTab3Clicked();
                    }//END ONCLICKED
                }//END BUTTON
            
            }//END TAB3 CONTAINER
        }
    }
}//END OUTTER CONTAINER
