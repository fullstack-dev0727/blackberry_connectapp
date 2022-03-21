import bb.cascades 1.4
import bb.device 1.4
import bb.system 1.2
import "../DetailScreens"
import "../custom"

Page {
    
    
    titleBar: TitleBar { 
        id: titleBar 
        kind: TitleBarKind.FreeForm  
        
        kindProperties: FreeFormTitleBarKindProperties { 
            id: kindProperties 
            content: Container { 
                background: Color.create("#2d85c2")
                layout: DockLayout {} 
                leftPadding: 40.0 
                rightPadding: 20.0 
                //ImageView { 0717
                //    imageSource: "asset:///images/titleicons/icon.png" 
                //    verticalAlignment: VerticalAlignment.Center 
                //    horizontalAlignment: HorizontalAlignment.Left
                //} 
                Label { 
                    text:  "Set default Locality"
                    textStyle.color: Color.White 
                    verticalAlignment: VerticalAlignment.Center
                    horizontalAlignment: HorizontalAlignment.Center
                
                } 
            } 
        } 
    } 
    
    actionBarAutoHideBehavior: ActionBarAutoHideBehavior.HideOnScroll

    
    Container {
        
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
        
        ActivityIndicator {
            id: actLoadingIndicator
            objectName: "actLoadingIndicator"
            verticalAlignment: VerticalAlignment.Center
            horizontalAlignment: HorizontalAlignment.Center
            preferredWidth: 100
            margin.topOffset: 20
        }
        
        
        Container {
            visible: (typeof _control.m_countryModel.Name === 'undefined' ? false: true) 
            
            margin.topOffset:  ui.du(3)
            layout: StackLayout {
                orientation: LayoutOrientation.TopToBottom
            }
            
            
            
            ListView {
                id: country_listview
                objectName: "country_listview"
                horizontalAlignment: HorizontalAlignment.Fill
                
                property bool loaded : false;

                
                function reloadCurrentUser() {
                    _home.loadMain();  
                    
                    myMessage.show();
                }
                
                function stopDialog() {
                    settingDef.close();  
                }
                
                onTriggered: {
                    if (indexPath > 0) {
                        var selectedItem = dataModel.data(indexPath);
                        _countrychooser.completedSignal.connect(reloadCurrentUser)
                        _countrychooser.completed.connect(stopDialog)
                        
                        
                        settingDef.open();
                        
                        _countrychooser.requestSetDefaultLocality(selectedItem.Id);
                        
                    }
                }
                
                function itemType(data, indexPath) {
                    return (indexPath == 0 ? "main" : "item");
                }
                
                
                
                listItemComponents: [
                    ListItemComponent {
                        type: "item"
                        Container {
                            id: container
                            horizontalAlignment: HorizontalAlignment.Fill
                            margin.topOffset:  ui.sdu(4)
                            margin.bottomOffset:  ui.sdu(4)
                            preferredWidth: maxWidth
                            
                            
                            
                            layout: DockLayout {}
                            
   
                                
                                ConnectLabel {
                                    horizontalAlignment: HorizontalAlignment.Left
                                    verticalAlignment: VerticalAlignment.Center
                                    margin.leftOffset:  ui.sdu(3)
                                    text: ListItemData.Name 
                                    textStyle {
                                        base: SystemDefaults.TextStyles.BodyText
                                        color: Color.DarkGray
                                    }
                                }
                                
                                ImageView {
                                    horizontalAlignment: HorizontalAlignment.Right
                                    visible: container.ListItem.view.isDefault(ListItemData.Id)
                                    imageSource: "asset:///images/img/locality_default.png"
                                    margin.rightOffset:  ui.sdu(3)
                                    preferredHeight: ui.sdu(6)
                                    preferredWidth: ui.sdu(6)
                                }
                            
                                                        
                        
                        }                        
                    },
                    ListItemComponent {
                        type: "main"
                        
                        
                        Container {
                            
                            horizontalAlignment: HorizontalAlignment.Fill
                            
                            onCreationCompleted: {
                                if (!mainItem.ListItem.view.loaded)
                                    mainItem.ListItem.view.loadLocalities(ListItemData.Code);
                                mainItem.ListItem.view.loaded = true;
                            }
                            
                            
                            id: mainItem
                            layout: StackLayout {
                                orientation: LayoutOrientation.TopToBottom
                            }
                            
                            
                            //Current Locality
                            Container {
                                layout: DockLayout {
                                
                                }
                                margin.topOffset: ui.sdu(3)
                                margin.bottomOffset: ui.sdu(3)
                                margin.leftOffset: ui.sdu(3)
                                margin.rightOffset: ui.sdu(3)
                                horizontalAlignment: HorizontalAlignment.Fill
                                preferredWidth: maxWidth
                                
                                ConnectLabel {
                                    text: "Current Default:"
                                    textStyle.color: Color.DarkGray
                                    horizontalAlignment: HorizontalAlignment.Left 
                                    verticalAlignment: VerticalAlignment.Center 
                                }                
                                ConnectLabel {
                                    text: mainItem.ListItem.view.getLocalityName()
                                    textStyle.color:  Color.create("#2d85c2")
                                    horizontalAlignment: HorizontalAlignment.Right
                                    verticalAlignment: VerticalAlignment.Center 
                                }
                            
                            
                            
                            }              
                                                        
                            Container {
                                horizontalAlignment: HorizontalAlignment.Fill
                                preferredWidth: maxWidth
                                layout: DockLayout {
                                    
                                
                                }
                                margin.bottomOffset:  ui.du(2)
                                margin.leftOffset:  ui.du(3)
                                margin.rightOffset:  ui.du(3)
                                
                                
                                Container {
                                    layout: StackLayout {
                                        orientation: LayoutOrientation.LeftToRight
                                    }
                                    
                                    
                                    horizontalAlignment: HorizontalAlignment.Left
                                    
                                    verticalAlignment: VerticalAlignment.Center
                                    
                                    Container {
                                        layout: DockLayout {
                                        
                                        }
                                        
                                        verticalAlignment: VerticalAlignment.Center
                                        horizontalAlignment: HorizontalAlignment.Center
                                        
                                        
                                        ImageView {
                                            preferredHeight: ui.sdu(12)
                                            preferredWidth: ui.sdu(12)
                                            
                                            horizontalAlignment: HorizontalAlignment.Center
                                            imageSource: "asset:///images/buttonimages/ellipse.png"
                                            filterColor: Color.create("#ff0EBAB4")
                                        }
                                        
                                        ConnectLabel {
                                            
                                            horizontalAlignment: HorizontalAlignment.Center
                                            verticalAlignment: VerticalAlignment.Center
                                            
                                            text: ListItemData.Code
                                            textStyle.color: Color.White
                                            textStyle.fontWeight: FontWeight.W500
                                            textStyle.fontSize: FontSize.Large
                                        
                                        }                    
                                    
                                    }
                                    
                                    ConnectLabel {
                                        text: ListItemData.Name
                                        margin.bottomOffset: ui.sdu(2)
                                        margin.leftOffset: ui.sdu(1.2)
                                        verticalAlignment: VerticalAlignment.Center
                                        textStyle {
                                            base: SystemDefaults.TextStyles.TitleText;
                                            color: Color.create("#2d85c2")
                                        }
                                    
                                    }
                                }
                                
                                
                                Container {
                                    layout: StackLayout {
                                        orientation: LayoutOrientation.LeftToRight
                                    }
                                    
                                    
                                    horizontalAlignment: HorizontalAlignment.Right
                                    verticalAlignment: VerticalAlignment.Center
                                    
                                    ImageView {
                                        verticalAlignment: VerticalAlignment.Center
                                        preferredHeight: ui.sdu(6)
                                        preferredWidth: ui.sdu(4)
                                        
                                        imageSource: "asset:///images/titleicons/locality_icon.png"
                                    }
                                    
                                    ConnectLabel {
                                        verticalAlignment: VerticalAlignment.Center
                                        text: ListItemData.LocalitiesCount + (ListItemData.LocalitiesCount == 1 ? " Locality" : " Localities")
                                        
                                        textStyle {
                                            base: SystemDefaults.TextStyles.BodyText;
                                            color: Color.Gray
                                        }
                                    
                                    }
                                
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
                        
                        
                                     
                        }
                    
                    }
                ]
                
                function loadLocalities(code) {
                    _control.requestLocalities(code, 1);
                }
                
                function isDefault(locId) {
                    return _countrychooser.isDefaultLocality(locId);
                }
                
                function getLocalityName() {
                    return _control.currentLocalityName;
                }
                
            }
        }
    
    
    attachedObjects: [
        Dialog {
            id: settingDef
            
            
            Container {
                layout: DockLayout {
                
                }
                preferredWidth: maxWidth
                preferredHeight: displayInfo.resolution.height;
                
                onCreationCompleted: {
                    actvIndicator.start();
                }
                
                Container {
                    horizontalAlignment: HorizontalAlignment.Fill
                    verticalAlignment: VerticalAlignment.Fill
                    background: Color.create("#AA000000");
                    
                    layout: DockLayout {
                    
                    } 
                    
                    
                    
                    Container {
                        layout: StackLayout {
                            orientation: LayoutOrientation.LeftToRight
                        
                        }
                        
                        horizontalAlignment: HorizontalAlignment.Center
                        verticalAlignment: VerticalAlignment.Center
                        
                        Container {
                            layoutProperties: StackLayoutProperties {
                                spaceQuota: 0.2    
                            }
                        
                        }
                        
                        Container {
                            layoutProperties: StackLayoutProperties {
                                spaceQuota: 1    
                            }
                            horizontalAlignment: HorizontalAlignment.Fill
                            verticalAlignment: VerticalAlignment.Fill
                            
                            
                            Container {
                                layout: DockLayout {
                                
                                }
                                
                                ImageView {
                                    preferredWidth: maxWidth
                                    
                                    imageSource: "asset:///images/nineslice/rounded.amd"
                                    horizontalAlignment: HorizontalAlignment.Fill
                                    verticalAlignment: VerticalAlignment.Fill
                                    filterColor: Color.LightGray
                                }
                                
                                
                                Container {
                                    horizontalAlignment: HorizontalAlignment.Fill
                                    verticalAlignment: VerticalAlignment.Fill
                                    
                                    
                                    layout: StackLayout {
                                        orientation: LayoutOrientation.TopToBottom
                                    }
                                    ConnectLabel {
                                        margin.topOffset: ui.sdu(3)
                                        margin.leftOffset: ui.sdu(4)
                                        
                                        text: "Setting Default Locality."
                                        textStyle.color: Color.Black
                                        textStyle.fontSize: FontSize.Medium   
                                    }
                                    
                                    Container {
                                        layout: StackLayout {
                                            orientation: LayoutOrientation.LeftToRight
                                        }
                                        margin.topOffset: ui.sdu(3)
                                        margin.bottomOffset: ui.sdu(3)
                                        margin.leftOffset: ui.sdu(4)
                                        
                                        
                                        ActivityIndicator {
                                            
                                            verticalAlignment: VerticalAlignment.Center
                                            id: actvIndicator
                                            enabled: true
                                            
                                            
                                            preferredHeight: ui.sdu(8)
                                            preferredWidth: ui.sdu(8)
                                        }
                                        
                                        ConnectLabel {
                                            margin.leftOffset: ui.sdu(2)
                                            verticalAlignment: VerticalAlignment.Center
                                            text: "Please wait..."
                                            textStyle.color: Color.DarkGray 
                                            textStyle.fontSize: FontSize.Small 
                                        
                                        }
                                    }
                                
                                }
                            
                            }
                        
                        
                        
                        
                        
                        
                        }
                        
                        Container {
                            layoutProperties: StackLayoutProperties {
                                spaceQuota: 0.2    
                            }
                        
                        }
                    
                    
                    }
                }
                
                attachedObjects: [
                    DisplayInfo {
                        id: displayInfo
                    },
                    SystemToast {
                        id: myMessage
                        body: "Your default locality has been changed."
                    }
                    
                ]        
            }
        
        
        }        
    ]
    }
}
