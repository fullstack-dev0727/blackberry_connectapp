import bb.cascades 1.4
import my.library 1.0
import "../custom"

Page {
    
    
    titleBar: TitleBar { 
        id: titleBar 
        kind: TitleBarKind.FreeForm  
        
        kindProperties: FreeFormTitleBarKindProperties { 
            id: kindProperties 
            content: Container { 
                background:  Color.create("#2d85c2")
                layout: DockLayout {} 
                leftPadding: 40.0 
                rightPadding: 20.0 
                
                ConnectLabel { 
                    text:  "Upgrade your plan"
                    textStyle.color:  Color.White
                    verticalAlignment: VerticalAlignment.Center
                    horizontalAlignment: HorizontalAlignment.Center
                
                }             
            } 
        } 
    } 
    
    Container {


        

        
        Container {
            verticalAlignment: VerticalAlignment.Fill
            horizontalAlignment: HorizontalAlignment.Fill
            layout: StackLayout {
                orientation: LayoutOrientation.TopToBottom
            }
        
            ConnectLabel { 
                margin.topOffset: ui.sdu(10)
                margin.leftOffset: ui.sdu(5)
                margin.rightOffset: ui.sdu(5)
                text:  "Seems like you don't have access to all Regions. Upgrade your plan to search for members from all around the world"
                textStyle.textAlign: TextAlign.Center
                multiline: true
                textStyle.color: Color.DarkGray 
                
                verticalAlignment: VerticalAlignment.Center
                horizontalAlignment: HorizontalAlignment.Center
            
            } 
            
            
            ImageView {
                margin.topOffset: ui.sdu(10)
                imageSource: "asset:///images/img/external_icon.png"
                horizontalAlignment: HorizontalAlignment.Center
                filterColor: Color.create("#2d85c2")
            }
            ConnectLabel { 
                text:  "Manage Subscription"
                textStyle.color:  Color.create("#2d85c2")
                textStyle.fontSize: FontSize.Large
                verticalAlignment: VerticalAlignment.Center
                horizontalAlignment: HorizontalAlignment.Center
            
            } 
        
        
            
        }
    
    
    }
}
