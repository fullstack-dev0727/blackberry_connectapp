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
                    text:  "Choose a country to filter by"
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
                objectName: "country_listview"
                
                margin.topOffset: 30
                
                
                onTriggered: {
                    var selectedItem = dataModel.data(indexPath);
                    _control.selectCountry(selectedItem.Code, selectedItem.Name);
                    
                    _main.updateFilter(selectedItem.Name);    
                    

                }
                                
                listItemComponents: [
                    ListItemComponent {
                        type: "item"
                        CustomListItem {
                            dividerVisible: true
                            
                            Container {
                                
                                margin.topOffset: ui.sdu(3)
                                margin.leftOffset: ui.sdu(3)
                                margin.rightOffset: ui.sdu(3)
                                
                                layout: DockLayout {}
                                
                                Container {
                                    layout: StackLayout {
                                        orientation: LayoutOrientation.TopToBottom
                                    }
                                    
                                    ConnectLabel {
                                        horizontalAlignment: HorizontalAlignment.Left
                                        verticalAlignment: VerticalAlignment.Center
                                        
                                        text: ListItemData.Name  
                                        textStyle {
                                            base: SystemDefaults.TextStyles.BodyText
                                            color: Color.Black
                                        }
                                    }
                                }
                            }
                        }                 
                    }
                ]
            }
        }
    
    
    
    }
}
