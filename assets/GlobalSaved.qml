import bb.cascades 1.4

import bb.cascades 1.4

Container {
    layout: StackLayout {
        orientation: LayoutOrientation.TopToBottom
    }
    
    
    Container {
        id: containerHomeTop
        layoutProperties: StackLayoutProperties {
            spaceQuota: 2.9
        }
        
        layout: StackLayout {
            orientation: LayoutOrientation.TopToBottom    
        }
        
        horizontalAlignment: HorizontalAlignment.Fill
        verticalAlignment: VerticalAlignment.Center
        
        background: back.imagePaint  
        
        
        
        Container {
            layoutProperties: StackLayoutProperties {
                
                spaceQuota: 1
            }
        }          
        
        Container {
            id: filterCard
            layoutProperties: StackLayoutProperties {
                spaceQuota: 1.5
            }
            
            verticalAlignment: VerticalAlignment.Center
            horizontalAlignment: HorizontalAlignment.Center
            
            
            Container {
                layout: StackLayout {
                    orientation: LayoutOrientation.TopToBottom
                }
                background: Color.Gray
                
                Container {
                    layout: StackLayout {
                        orientation: LayoutOrientation.LeftToRight
                    }
                    
                    ImageView {
                        imageSource: "asset:///images/titleicons/icon_search.png"
                        preferredHeight: ui.sdu(9)
                        preferredWidth: ui.sdu(9)
                    }
                    
                    Label {
                        text: "Search people and places"
                    }
                
                
                }                
                
                Container {
                    layout: StackLayout {
                        orientation: LayoutOrientation.LeftToRight
                    }
                    
                    
                    Label {
                        text: "Filter by country"
                    }
                    
                    Button {
                        
                        id: btCountryFilter
                        objectName: "btCountryFilter"
                        
                        text: "All"
                        
                        onClicked: {
                            _control.selectCountryFilter();
                        }
                    }
                }
            }
        }
        attachedObjects: [
            ImagePaintDefinition {
                id: back
                repeatPattern: RepeatPattern.XY
                imageSource: "asset:///images/img/bg_login_screen.jpg"
            }
        ]        
    }
    
    Container {
        id: containerHomeBottom
        layoutProperties: StackLayoutProperties {
            spaceQuota: 2
        }
        minHeight: 
        
        
        Container {
            id: localityCard
            
            layout: StackLayout {
                orientation: LayoutOrientation.TopToBottom
            }
            
            margin.topOffset: ui.sdu(2)
            margin.leftOffset: ui.sdu(3)
            margin.rightOffset: ui.sdu(3)
            
            Label {
                text: "My default location"
                textStyle.color: Color.Black
            }
            
            Container {
                id: containerDefaultLocationBt
                
                margin.topOffset: ui.sdu(2)
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }
                
                margin.bottomOffset: ui.sdu(5)
                
                Button {
                    id: localityNameBt
                    
                    color: Color.Transparent                                                        
                    text: "Browse" +  _control.m_currentUserModel.DefaultLocality.Name
                    
                    onClicked: {
                        _control.openDefLocality();
                    }
                
                }
                
                Button {
                    id: countryName
                    
                    color: Color.Transparent                                                        
                    margin.leftOffset: ui.sdu(3)
                    text: "Browse" +  _control.m_currentUserModel.DefaultCountry.Name
                    
                    onClicked: {
                        _control.openDefCountry();
                    }
                
                }
            
            }
        
        
        }
        
        
        Container {
            id: countryListCard
            
            layout: StackLayout {
                orientation: LayoutOrientation.TopToBottom
            }
            
            margin.topOffset: ui.sdu(3)
            margin.leftOffset: ui.sdu(3)
            margin.rightOffset: ui.sdu(3)
            
            Label {
                margin.bottomOffset: 20
                text: "Browse Countries"
                textStyle.color: Color.Black
            }
            
            ListView {
                id: listViewCountries
                dataModel: _control.m_countriesModel
                scrollRole: ScrollRole.None
                
                onTriggered: {
                    var selectedItem = dataModel.data(indexPath);
                    _control.openCountry(selectedItem.Code, selectedItem.Name);    
                }
                
                listItemComponents: [
                    ListItemComponent {
                        type: "item"
                        
                        CustomListItem {
                            dividerVisible: true
                            
                            Container {
                                
                                layout: DockLayout {}
                                
                                Container {
                                    layout: StackLayout {
                                        orientation: LayoutOrientation.TopToBottom
                                    }
                                    
                                    Label {
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