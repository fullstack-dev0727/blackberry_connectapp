import bb.cascades 1.4

// Groups all the visual nodes for the grogress bar
Container {
    id: root
    
    // The total progress bar value
    property int total: 0
    
    // The current progress
    property int value: 0
    
    property alias message: messageLabel.text
    
    preferredWidth: 1000
    
    layout: DockLayout {}
    
    // Container for the progress bar identifying the Layout
    Container {
        horizontalAlignment: HorizontalAlignment.Fill
        verticalAlignment: VerticalAlignment.Fill
        
        layout: AbsoluteLayout {}
        
        // Container representing the size and color of the bar
        Container {
            background: Color.Blue
            
            // Bar width changing depending on the current value
            preferredWidth: root.total == 0 ? 0 : root.value * root.preferredWidth / root.total
            preferredHeight: 40
            
            layoutProperties: AbsoluteLayoutProperties {
                positionX: 0
                positionY: 0
            }
            
            // Disable animation of preferredWidth property
            attachedObjects: ImplicitAnimationController {
                propertyName: "preferredWidth"
                enabled: false
            }
        }
    }
    
    // A standard Label for the bar message
    Label {
        id: messageLabel
        
        horizontalAlignment: HorizontalAlignment.Center
        verticalAlignment: VerticalAlignment.Center
        
        textStyle.color: Color.Black
        textStyle.base: SystemDefaults.TextStyles.SmallText
    }
}