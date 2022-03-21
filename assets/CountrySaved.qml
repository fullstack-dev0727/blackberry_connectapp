import bb.cascades 1.4

Container {
    id: containerHomeTop
    
    
    onCreationCompleted: {
        loadFilterBt();
    }
    
    layout: StackLayout {
        orientation: LayoutOrientation.TopToBottom    
    }
    
    horizontalAlignment: HorizontalAlignment.Fill
    
    Container {
        id: imageNFilterContainer
        
        background: back.imagePaint
        
        horizontalAlignment: HorizontalAlignment.Fill
        
        minHeight: 840
        preferredHeight: 840
        
        Container {
            layoutProperties: StackLayoutProperties {
                spaceQuota: 0.7
            }
        }
        
        Container {
            id: filterCard
            
            verticalAlignment: VerticalAlignment.Center
            horizontalAlignment: HorizontalAlignment.Center
            
            layoutProperties: StackLayoutProperties {
                spaceQuota: 1
            }
            
            
            Container {
                layout: StackLayout {
                    orientation: LayoutOrientation.TopToBottom
                }
                background: Color.White
                
                Container {
                    layout: StackLayout {
                        orientation: LayoutOrientation.LeftToRight
                    }
                    
                    ImageView {
                        imageSource: "asset:///images/titleicons/icon_search.png"
                        preferredHeight: ui.sdu(9)
                        preferredWidth: ui.sdu(9)
                    }
                    
                    ConnectLabel {
                        text: "Search people and places"
                        
                        textStyle.color: Color.Gray
                    }
                
                
                }                
            }
        }
        attachedObjects: [
            ImagePaintDefinition {
                id: back
                repeatPattern: RepeatPattern.XY
                imageSource: "asset:///images/img/top_home_screen.jpg"
            }
        ]                                    
    }  
    
    Container {
        id: localityCard
        
        layout: StackLayout {
            orientation: LayoutOrientation.TopToBottom
        }
        
        margin.topOffset: ui.sdu(3)
        margin.leftOffset: ui.sdu(3)
        margin.rightOffset: ui.sdu(3)
        
        
        
        ConnectLabel {
            text: "My default location"
            textStyle.color: Color.Gray
        }
        
        Container {
            id: containerDefaultLocationBt
            
            layout: StackLayout {
                orientation: LayoutOrientation.LeftToRight
            }
            
            horizontalAlignment: HorizontalAlignment.Fill
            
            margin.topOffset: ui.sdu(3)
            margin.bottomOffset: ui.sdu(1)
            
            Container {
                
                layoutProperties: StackLayoutProperties {
                    spaceQuota: 1
                }
                
                layout: StackLayout {
                    orientation: LayoutOrientation.TopToBottom
                }
                horizontalAlignment: HorizontalAlignment.Center
                
                ImageView {
                    horizontalAlignment: HorizontalAlignment.Center
                    imageSource: "asset:///images/buttonimages/ellipse.png"
                    filterColor: Color.Red
                }
                
                
                ConnectLabel {
                    id: localityNameBt
                    horizontalAlignment: HorizontalAlignment.Center
                    
                    text: "Browse " +  ListItemData.DefaultLocality.Name
                    textStyle.color: Color.Black
                }
                
                ConnectLabel {
                    id: localitySubQt
                    horizontalAlignment: HorizontalAlignment.Center
                    
                    text: ListItemData.DefaultLocality.SubdivisionCount + " subdivisions"
                    textStyle.color: Color.Gray
                }
                
                gestureHandlers: [
                    
                    TapHandler {
                        onTapped: {
                            containerHomeTop.ListItem.view.localityBrowse();
                        
                        }
                    }
                ]
            
            }                                        
            
            Container {
                layoutProperties: StackLayoutProperties {
                    spaceQuota: 1
                }
                
                layout: StackLayout {
                    orientation: LayoutOrientation.TopToBottom
                }
                horizontalAlignment: HorizontalAlignment.Center
                
                
                ImageView {
                    horizontalAlignment: HorizontalAlignment.Center
                    imageSource: "asset:///images/buttonimages/ellipse.png"
                    filterColor: Color.Cyan
                }
                
                ConnectLabel {
                    id: countryName
                    horizontalAlignment: HorizontalAlignment.Center
                    
                    textStyle.color: Color.Black
                    text: ListItemData.DefaultCountry.Name
                }
                
                ConnectLabel {
                    id: countryLocCount
                    horizontalAlignment: HorizontalAlignment.Center
                    
                    textStyle.color: Color.Gray
                    text: ListItemData.DefaultCountry.LocalitiesCount + (ListItemData.DefaultCountry.LocalitiesCount == 1 ? " locality" : " localities")
                }
                
                gestureHandlers: [
                    
                    TapHandler {
                        onTapped: {
                            
                            containerHomeTop.ListItem.view.countryBrowse();
                        
                        }
                    }
                ]                                            
            }
        
        
        }
    
    
    }       

} 