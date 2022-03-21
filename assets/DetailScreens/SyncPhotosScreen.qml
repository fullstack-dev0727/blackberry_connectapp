import bb.cascades 1.4
import my.library 1.0
import "../custom"

// This page shows how to layout various standard visual components along with a custom component.
Page {
    
    Container {
        layout: StackLayout {
            orientation: LayoutOrientation.TopToBottom
        }    
        horizontalAlignment: HorizontalAlignment.Fill
        verticalAlignment: VerticalAlignment.Fill
        onTouch: {
            _control.onTouchFunc();
        }
        Container {
            horizontalAlignment: HorizontalAlignment.Fill
            layout: DockLayout {
            }
        
        Container { 
            
            background: Color.create("#2d85c2") //blue
            layout: StackLayout { orientation: LayoutOrientation.TopToBottom} 
            topPadding: 20.0 
            bottomPadding: 20.0
            horizontalAlignment: HorizontalAlignment.Fill
            
            
            ConnectLabel { 
                visible: (typeof _control.m_localityModel.Name === 'undefined' ? false: true)
                text: _manager.database ? "Downloading Photo data" : "Syncing photos"
                textStyle.color: Color.White 
                horizontalAlignment: HorizontalAlignment.Center
            
            } 
            
            
            ConnectLabel {
                visible: (typeof _control.m_localityModel.Name === 'undefined' ? false: true)
                id: labelInfo 
                text: "This may take a while."
                textStyle.color: Color.White 
                textStyle.fontSize: FontSize.Small
                horizontalAlignment: HorizontalAlignment.Center
            
            }
        } 
        ConnectLabel {
            horizontalAlignment: HorizontalAlignment.Left
            verticalAlignment: VerticalAlignment.Center
            text: "Finish Later"
            margin.leftOffset: ui.sdu(3)
            textStyle.color: Color.White
            textStyle.fontSize: FontSize.XXSmall
            textStyle.fontWeight: FontWeight.Bold
            textFormat: TextFormat.Html
            gestureHandlers: [
                TapHandler {
                    onTapped: {
                        _sheet.close();
                    }
                }
            ]
        }
    }
        // The root Container
        Container {
            layout: DockLayout {}
            
            Container {
                horizontalAlignment: HorizontalAlignment.Fill
                verticalAlignment: VerticalAlignment.Fill
                
                leftPadding: 30
                topPadding: 20
                rightPadding: 30
                
                // A standard Label
                Label {
                    topMargin: 10
                    leftMargin: 10
                    
                    text: qsTr("Download progress")
                    textStyle.base: SystemDefaults.TextStyles.BodyText
                    textStyle.color: Color.Black
                }
                
                // Custom Container for displaying download progress as a bar
                ProgressBar {
                    topMargin: 10
                    leftMargin: 10
                    
                    total: _manager.progressTotal
                    value: _manager.progressValue
                    message: _manager.progressMessage
                }
                
                // A standard Label
                Label {
                    topMargin: 10
                    leftMargin: 10
                    
                    text: qsTr("Active Downloads: ") + (_manager.activeDownloads == 0 ? "none" : _manager.activeDownloads)
                    textStyle.base: SystemDefaults.TextStyles.BodyText
                    textStyle.color: Color.Black
                }
                
                // A standard Label
                Label {
                    topMargin: 10
                    leftMargin: 10
                    
                    text: qsTr("Status:")
                    textStyle.base: SystemDefaults.TextStyles.BodyText
                    textStyle.color: Color.Black
                }
                
                // A standard TextArea for the download status output
                TextArea {
                    preferredWidth: maxWidth
                    preferredHeight: 350
                    
                    backgroundVisible: false
                    editable: false
                    
                    text: _manager.statusMessage
                    
                    // Defines text style with custom Color
                    textStyle {
                        base: SystemDefaults.TextStyles.BodyText
                        color: Color.create("#ff509d4c")
                    }
                }
                
                // A standard Label
                Label {
                    leftMargin: 10
                    
                    text: qsTr ("Errors:")
                    textStyle.base: SystemDefaults.TextStyles.BodyText
                    textStyle.color: Color.Black
                }
                
                // A standard TextArea for displaying error output
                TextArea {
                    leftMargin: 10
                    preferredWidth: maxWidth
                    preferredHeight: 150
                    
                    backgroundVisible: false
                    editable: false
                    
                    text: _manager.errorMessage
                    
                    // Defines a text style with custom Color
                    textStyle {
                        base: SystemDefaults.TextStyles.SmallText
                        color: Color.create("#ffbc3434")
                    }
                }
            }
        }
    }

}