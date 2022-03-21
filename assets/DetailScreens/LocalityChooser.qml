import bb.cascades 1.4

Page {
    
    
    titleBar: TitleBar { 
        id: titleBar 
        kind: TitleBarKind.FreeForm  
        
        kindProperties: FreeFormTitleBarKindProperties { 
            id: kindProperties 
            content: Container { 
                background: Color.Blue
                layout: DockLayout {} 
                leftPadding: 40.0 
                rightPadding: 20.0 
                ImageView { 
                    imageSource: "asset:///images/titleicons/icon.png" 
                    verticalAlignment: VerticalAlignment.Center 
                    horizontalAlignment: HorizontalAlignment.Left
                } 
                Label { 
                    text:  "Filter"
                    textStyle.color: Color.White 
                    verticalAlignment: VerticalAlignment.Center
                    horizontalAlignment: HorizontalAlignment.Center
                
                } 
            } 
        } 
    } 
    
    Container {
        onTouch: {
            _control.onTouchFunc();
        }
        Container {
            visible: _control.error
            layout: StackLayout {
                orientation: LayoutOrientation.TopToBottom
            }
            margin.topOffset: ui.sdu(10)
            horizontalAlignment: HorizontalAlignment.Fill
            
            ImageView {
                imageSource: "asset:///images/img/icon_warning.png"
                verticalAlignment: VerticalAlignment.Center
                horizontalAlignment: HorizontalAlignment.Center
            }
            
            Label {
                verticalAlignment: VerticalAlignment.Center
                horizontalAlignment: HorizontalAlignment.Center
                multiline: true
                margin.leftOffset: ui.sdu(5);
                margin.rightOffset: ui.sdu(5);
                
                text: _control.errorMessage
                textStyle {
                    base: SystemDefaults.TextStyles.PrimaryText;
                    color: Color.DarkGray
                    textAlign: TextAlign.Center 
                }
            
            }
        }
        
        Container {
            layout: StackLayout {
                orientation: LayoutOrientation.TopToBottom
            }
            
            Label {
                text: "Choose a locality as your default locality"
                textStyle {
                    base: SystemDefaults.TextStyles.BigText;
                    color: Color.Black
                }
            
            }
            
            ActivityIndicator {
                id: contentLoadingIndicator
                objectName: "contentLoadingIndicator"
                verticalAlignment: VerticalAlignment.Center
                horizontalAlignment: HorizontalAlignment.Center
                preferredWidth: 100
                margin.topOffset: 20
            }
            
            ListView {
                id: country_listview
                objectName: "locality_listview"
                
                margin.topOffset: 30
                
                
                onTriggered: {
                    var selectedItem = dataModel.data(indexPath);
                    _control.selectCountry(selectedItem.Id, selectedItem.Name);    
                }
                                
                listItemComponents: [
                    ListItemComponent {
                        type: "item"
                        Container {
                            
                            preferredWidth: ui.du(85.3)
                            preferredHeight: ui.du(22.2)    
                            
                            layout: DockLayout {}
                            
                            Container {
                                horizontalAlignment: HorizontalAlignment.Left
                                leftPadding: ui.du(2.2)
                                rightPadding: ui.du(2.2)
                                
                                Label {
                                    horizontalAlignment: HorizontalAlignment.Left
                                    verticalAlignment: VerticalAlignment.Center
                                    
                                    text: ListItemData.Name 
                                    textStyle {
                                        base: SystemDefaults.TextStyles.BodyText
                                        color: Color.Black
                                    }
                                }
                                
                                Label {
                                    preferredHeight: ui.du(22.2)
                                    
                                    text: "Locality" 
                                    textStyle {
                                        base: SystemDefaults.TextStyles.SmallText
                                        color: Color.Blue
                                    }
                                    
                                    multiline: true
                                }
                            }                            
                        
                        }                        
                    }
                ]
            }
        }
    
    
    
    }
}
