import bb.cascades 1.4
import bb.device 1.4
import bb.system 1.2
import "DetailScreens"
import "custom"
import "var.js" as Var

Sheet {
    id: walkthroughSheet
    
    peekEnabled: false
    
    
    onOpened: {
    }
    
    Page {
        resizeBehavior: PageResizeBehavior.None
        
        Container {
            horizontalAlignment: HorizontalAlignment.Fill
            verticalAlignment: VerticalAlignment.Fill
            
            onTouch: {
                _control.onTouchFunc();
            }
                
            
            
            ImageView {
                id: imageV
                horizontalAlignment: HorizontalAlignment.Fill
                verticalAlignment: VerticalAlignment.Fill
                imageSource: "asset:///images/walkthrough/page1.jpg"
                
                
                function getNext() {
                    if (Var.screen === 1) 
                        imageV.imageSource = "asset:///images/walkthrough/page2.jpg"
                    else if (Var.screen === 2) 
                        imageV.imageSource = "asset:///images/walkthrough/page3.jpg"
                    Var.screen = Var.screen + 1;    
                
                }
                onTouch: {
                    
                    if (event.touchType == TouchType.Down) {
                        //Do something on down touch - e.g. change background color
                    } else if (event.touchType == TouchType.Up || event.touchType == TouchType.Cancel)     {
                        //Users finger has been lifted OR has left the element.
                        onClicked: {
                            (Var.screen === 3 ? close() : getNext());                            
                        }
                    }
                }        
            

            }
            
        }
            
          
    }
    
    attachedObjects: [
        DisplayInfo {
            id: displayInfo
        }
    ]

}