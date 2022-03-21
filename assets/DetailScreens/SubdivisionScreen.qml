import bb.cascades 1.4
import my.library 1.0
import "../custom"
import bb.platform 1.3


Page {

    onCreationCompleted: {
        _control.loadSubdivision.connect(load)
    }
    
    function load() {
        _control.requestSubdivision(_control.getId())
    }
    
    actions: [
        ActionItem {
            id: homeAction
            objectName: "homeAction"
            title: "Home"
            imageSource: "asset:///images/titleicons/icon_home.png"
            ActionBar.placement: ActionBarPlacement.OnBar
            onTriggered: {
                _control.openAction(homeAction.objectName);
            }
        },
        ActionItem {
            id: searchAction
            objectName: "searchAction"
            title: "Search"
            imageSource: "asset:///images/titleicons/icon_search.png" 
            ActionBar.placement: ActionBarPlacement.OnBar
            onTriggered: {
                _control.openAction(searchAction.objectName);
            }                                        
        },
        ActionItem {
            id: detailsAction
            objectName: "detailsAction"
            title: "My Details"
            imageSource: "asset:///images/menuicons/my_details.png" 
            ActionBar.placement: ActionBarPlacement.InOverflow                                        
            onTriggered: {
                _control.openAction(detailsAction.objectName);
            }                                        
        },
        ActionItem {
            id: locationAction
            objectName: "locationAction"
            title: "Default Locality"
            imageSource: "asset:///images/menuicons/my_default_locality.png" 
            ActionBar.placement: ActionBarPlacement.InOverflow                                        
            onTriggered: {
                _control.openAction(locationAction.objectName);
            }                                        
        },
        ActionItem {
            id: termsAction
            objectName: "termsAction"
            title: "Term and conditions"
            imageSource: "asset:///images/menuicons/terms_n_conditions.png" 
            ActionBar.placement: ActionBarPlacement.InOverflow                                        
            onTriggered: {
                _control.openAction(termsAction.objectName);
            }                                        
        },
        ActionItem {
            id: contactAction
            objectName: "contactAction"
            title: "Contact UBT"
            imageSource: "asset:///images/menuicons/contact_ubt.png" 
            ActionBar.placement: ActionBarPlacement.InOverflow                                        
            onTriggered: {
                _control.openAction(contactAction.objectName);
            }                                        
        },
        ActionItem {
            id: syncAction
            objectName: "syncAction"
            title: "Sync Data"
            imageSource: "asset:///images/menuicons/security.png" 
            ActionBar.placement: ActionBarPlacement.InOverflow                                        
            onTriggered: {
                _control.openAction(syncAction.objectName);
            }                                        
        },
        ActionItem {
            id: feedbackAction
            objectName: "feedbackAction"
            title: "Feedback"
            imageSource: "asset:///images/menuicons/contact_ubt.png" 
            ActionBar.placement: ActionBarPlacement.InOverflow                                        
            onTriggered: {
                _control.openAction(feedbackAction.objectName);
            }                                        
        },
        ActionItem {
            ActionBar.placement: ActionBarPlacement.InOverflow                                        
            title: "Log out"
            imageSource: "asset:///images/menuicons/logout.png" 
            onTriggered: {
                _home.logout();
            
            
            }
        }
    ]
    
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
            visible: _control.noPermission
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
        
            onTouch: {
                if (event.touchType == TouchType.Down) {
                    //Do something on down touch - e.g. change background color
                } else if (event.touchType == TouchType.Up || event.touchType == TouchType.Cancel)     {
                    //Users finger has been lifted OR has left the element.
                    onClicked: {
                        _control.manageSubs();
                    }
                }
            }        

        
        }
        
        
        
        ListView {
            id: locality_listview
            objectName: "subdivision_listview"
            visible: (typeof _control.m_subdivisonModel.Name === 'undefined' ? false: true) 
            
            scrollIndicatorMode: ScrollIndicatorMode.None
            
    
            
            
            function itemType(data, indexPath) {
                return (indexPath == 0 ? "main" : "item");
            }
            
            function openLocality(localityId) {
                _control.openLocality(localityId);
            }
            
            onTriggered: {
                var selectedItem = dataModel.data(indexPath);
                if (indexPath > 0)
                    _control.openHousehold(selectedItem.itemData.HouseholderId, selectedItem.itemData.LastName)
            }
            
            listItemComponents: [
                ListItemComponent {
                    
                    type: "main" //Subdivision Header
                    
                    Container {
                        id: mainC
                        preferredHeight: ui.sdu(130)
                        horizontalAlignment: HorizontalAlignment.Fill
                        
                        layout: DockLayout {
                        
                        }
                        
                        Container {
                            verticalAlignment: VerticalAlignment.Fill
                            horizontalAlignment: HorizontalAlignment.Fill
                            
                            layout: StackLayout {
                                orientation: LayoutOrientation.TopToBottom
                            }
                            
                            Container {
                                background: Color.create("#2d85c2") //blue
                                horizontalAlignment: HorizontalAlignment.Fill
                                preferredWidth: maxWidth
                                
                                id: mainPhoto
                                
                                layoutProperties: StackLayoutProperties {
                                    spaceQuota: 1
                                }
                                
                                Container {
                                    id: pCont
                                    layout: DockLayout {
                                    
                                    }
                                    
                                    horizontalAlignment: HorizontalAlignment.Fill
                                    verticalAlignment: VerticalAlignment.Fill
                                    preferredHeight: mainPhoto.maxHeight
                                   
                                    // The ImageView that shows the loaded image after loading has finished with error or there is no image
                                    ImageView {
                                        id: notopImage
                                        margin.bottomOffset: ui.sdu(12)
                                        margin.topOffset: ui.sdu(12)
                                        margin.rightOffset: ui.sdu(23)
                                        margin.leftOffset: ui.sdu(23)
                                        scalingMethod: ScalingMethod.AspectFit
                                        horizontalAlignment: HorizontalAlignment.Center
                                        verticalAlignment: VerticalAlignment.Center
                                        
                                        imageSource: "asset:///images/img/no_image.png"
                                        visible: true
                                    }                                         

                                    Container {
                                        id: image
                                        horizontalAlignment: HorizontalAlignment.Fill
                                        verticalAlignment: VerticalAlignment.Fill
                                        layout: DockLayout {
                                        }
                                        function getUrl(url1, id, localityId, countryCode) {
                                            url1["id"] = id;       
                                            url1["localityId"] = localityId; 
                                            url1["countryCode"] = countryCode;  
                                            return url1; 
                                        }
                                        WebImageView {
                                            id: webViewImage
                                            url: image.getUrl(ListItemData.itemData.Photo.URL340, ListItemData.itemData.Photo.Id, ListItemData.itemData.Locality.Id, ListItemData.itemData.Country.Code)
                                            horizontalAlignment: HorizontalAlignment.Fill
                                            verticalAlignment: VerticalAlignment.Fill
                                            scalingMethod: ScalingMethod.AspectFit
                                            visible: (webViewImage.loading == 1.0 && !(typeof ListItemData.itemData.Photo === 'undefined'))
                                        }
                                        ProgressIndicator {
                                            value: webViewImage.loading
                                            horizontalAlignment: HorizontalAlignment.Center
                                            verticalAlignment: VerticalAlignment.Bottom
                                            visible: (webViewImage.loading < 1.0 && !(typeof ListItemData.itemData.Photo === 'undefined'))
                                        }
                                    }
           
                                    
                                
                                
                                }
                            
                            }
                            
                            Container {
                                horizontalAlignment: HorizontalAlignment.Fill
                                layout: DockLayout {
                                    //orientation: LayoutOrientation.TopToBottom
                                }
                                
                                id: mainContent
                                
                                layoutProperties: StackLayoutProperties {
                                    spaceQuota: 1
                                }
                                
                                
                                Container {
                                    layout: StackLayout {
                                        orientation: LayoutOrientation.TopToBottom
                                    }
                                    margin.topOffset: ui.sdu(11)
                                    verticalAlignment: VerticalAlignment.Top
                                    horizontalAlignment: HorizontalAlignment.Center
                                
                                
                                    ConnectLabel {
                                        horizontalAlignment: HorizontalAlignment.Center
                                        textFit.mode: LabelTextFitMode.FitToBounds
                                        
                                        textStyle {
                                            base: SystemDefaults.TextStyles.PrimaryText;
                                            color: Color.create("#FF37474F")
                                            textAlign: TextAlign.Center 
                                            fontSizeValue: 120
                                        }                                        
                                        text: "<b>"+ListItemData.itemData.Name+"</b>"  //+ "  " + _control.m_subdivisionModel.HouseholdCount + " households  " + _control.m_subdivisionModel.MemberCount + " brethren"
                                        
                                        multiline: true
                                    }
                                    
                                    ConnectLabel {
                                        horizontalAlignment: HorizontalAlignment.Center
                                        
                                        text: formatAddress(ListItemData.itemData.FormattedAddress);
                                        
                                        textStyle {
                                            base: SystemDefaults.TextStyles.SubtitleText;
                                            color: Color.create("#FF90A4AE")
                                            textAlign: TextAlign.Center 
                                            fontSizeValue: 95
                                        }
                                        multiline: true
                                        
                                        
                                        function formatAddress(address) {
                                            var ad = address.replace(/[\r\n]+/g," ");
                                            return ad;
                                        }
                                    } 
                                    
                                    Container {
                                        layout: DockLayout {
                                        }
                                        visible: typeof ListItemData.itemData.FormattedAddress === 'undefined' || (ListItemData.itemData.FormattedAddress === "") ? false : true
                                        
                                        gestureHandlers: [
                                            TapHandler {
                                                onTapped: { 
                                                    mainC.ListItem.view.openMap(ListItemData.itemData.FormattedAddress.replace(/[\r\n]+/g," "));
                                                }
                                            }
                                        ]
                                        
                                        horizontalAlignment: HorizontalAlignment.Fill
                                        verticalAlignment: VerticalAlignment.Bottom
                                        preferredHeight: ui.sdu(15)
                                        margin.topOffset: ui.sdu(4)
                                        background:Color.create("#fafafa")
                                        
                                        Divider {
                                            verticalAlignment: VerticalAlignment.Top
                                        }
                                        Divider {
                                            verticalAlignment: VerticalAlignment.Bottom
                                        }
                                        
                                        ImageView {
                                            scalingMethod: ScalingMethod.AspectFit
                                            horizontalAlignment: HorizontalAlignment.Center
                                            verticalAlignment: VerticalAlignment.Center
                                            
                                            preferredHeight: ui.sdu(7)
                                            preferredWidth: ui.sdu(7)
                                            
                                            imageSource: "asset:///images/titleicons/locality_icon.png"
                                        }
                                        
                                    }
                                    
                                
                                } 
                                
                               
                                
                                Container {
                                    layout: StackLayout {
                                        orientation: LayoutOrientation.TopToBottom
                                    }
                                    horizontalAlignment: HorizontalAlignment.Left
                                    verticalAlignment: VerticalAlignment.Bottom
                                    
                                    Container {
                                        layout: StackLayout {
                                            orientation: LayoutOrientation.LeftToRight
                                        }
                                        horizontalAlignment: HorizontalAlignment.Left
                                        verticalAlignment: VerticalAlignment.Bottom
                                        margin.bottomOffset: ui.sdu(4)
                                        margin.leftOffset: ui.sdu(2.2)
                                        
                                        
                                        ImageView {
                                            preferredHeight: ui.sdu(6)
                                            preferredWidth: ui.sdu(6)
                                            
                                            verticalAlignment: VerticalAlignment.Center                                        
                                            imageSource: "asset:///images/img/location_icon.png"  
                                        }
                                        
                                        ConnectLabel {
                                            verticalAlignment: VerticalAlignment.Center                                        
                                            textStyle.color: Color.create("#FF90A4AE")
                                            textStyle.fontSize: FontSize.Small
                                            
                                            text: "Locality: " + ListItemData.itemData.Locality.Name
                                        }
                                        
                                        gestureHandlers: [
                                            TapHandler {
                                                onTapped: {
                                                    mainC.ListItem.view.openLocality(ListItemData.itemData.Locality.Id)   
                                                }
                                            }
                                        ]
                                    }
                                    
                                    Container {
                                        layout: StackLayout {
                                            orientation: LayoutOrientation.LeftToRight
                                        }
                                        horizontalAlignment: HorizontalAlignment.Left
                                        verticalAlignment: VerticalAlignment.Bottom
                                        margin.bottomOffset: ui.sdu(4)
                                        margin.leftOffset: ui.sdu(2.2)
                                        
                                        
                                        ImageView {
                                            preferredHeight: ui.sdu(6)
                                            preferredWidth: ui.sdu(6)
                                            
                                            verticalAlignment: VerticalAlignment.Center                                        
                                            imageSource: "asset:///images/img/household_icon.png"  
                                        }
                                        
                                        ConnectLabel {
                                            verticalAlignment: VerticalAlignment.Center                                        
                                            textStyle.color: Color.create("#FF90A4AE")
                                            textStyle.fontSize: FontSize.Small
                                            
                                            text: ListItemData.itemData.HouseholdCount +  " households"
                                        }
                                    }
                                    
                                }
                            
                            }
                        
                        }
                        
                        
                        ImageView {
                            id: subdLogo
                            
                            verticalAlignment: VerticalAlignment.Center
                            horizontalAlignment: HorizontalAlignment.Center
                            
                            preferredHeight: ui.sdu(17)
                            preferredWidth: ui.sdu(17)
                            
                            imageSource: "asset:///images/img/subdivision_icon_fill.png"
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
                
                },
                ListItemComponent {
                    
                    type: "item" //Households
                    Container {
                        
                        preferredWidth: ui.du(85.3)
                        preferredHeight: ui.du(22.2)
                        
                        layout: DockLayout {}
                        
                        //GET KIDS NAMES
                        function getFamilyMemberNames() {
                            
                            var members = "";
                            
                            if (ListItemData.itemData.ChildrensFirstNames) {
                                var a = ListItemData.itemData.ChildrensFirstNames
                                var members = "";
                                a.forEach(function(entry) {
                                        if (members != "")
                                            members = members + ", ";
                                        members = members + entry;      
                                });
                            }
                            else if (ListItemData.itemData &&  ListItemData.itemData.FamilyMembers) {
                                var a = ListItemData.itemData.FamilyMembers
                                var members = "";
                                a.forEach(function(entry) {
                                        if (!(entry.IsHouseholder) && (entry.Householder.Id == ListItemData.itemData.Householder.Id) && !(ListItemData.itemData.IsDeceased)) {
                                            if (members != "")
                                                members = members + ", ";
                                            
                                            members = members + entry.FirstName;      
                                        }
                                });
                            }

                        
                        return members;
                        }
                        
                        Container {
                            layout: StackLayout {
                                orientation: LayoutOrientation.LeftToRight
                            }
                            
                            horizontalAlignment: HorizontalAlignment.Left
                            leftPadding: ui.du(2.2)
                            rightPadding: ui.du(2.2)
                            
                            Container {
                                layout: DockLayout {
                                
                                }
                                verticalAlignment: VerticalAlignment.Center
                                
                                minHeight: ui.sdu(22)
                                minWidth: ui.sdu(22)
                                preferredHeight: ui.sdu(22)
                                preferredWidth: ui.sdu(22)
                                
                                
                                ImageView {
                                    verticalAlignment: VerticalAlignment.Center
                                    
                                    minHeight: ui.sdu(22)
                                    minWidth: ui.sdu(22)
                                    preferredHeight: ui.sdu(22)
                                    preferredWidth: ui.sdu(22)
                                    scalingMethod: ScalingMethod.AspectFit 
                                    imageSource: "asset:///images/img/placeholder_household.png"
                                    
                                    visible: true
                                }
                                
                                Container {
                                    id: imageHousehold
                                    minHeight: ui.sdu(22)
                                    minWidth: ui.sdu(22)
                                    preferredHeight: ui.sdu(22)
                                    preferredWidth: ui.sdu(22)
                                    layout: DockLayout {
                                    }
                                    function getUrl(url1, id, localityId, countryCode) {
                                        url1["id"] = id;       
                                        url1["localityId"] = localityId; 
                                        url1["countryCode"] = countryCode;  
                                        return url1; 
                                    }
                                    WebImageView {
                                        id: webViewImage1
                                        url: imageHousehold.getUrl((ListItemData.itemData.Photo.URL340 ? ListItemData.itemData.Photo.URL340 : ""), ListItemData.itemData.Photo.Id + ListItemData.itemData.FirstName + ListItemData.itemData.LastName + ListItemData.itemData.Locality.Id + ListItemData.itemData.Country.Code)
                                        horizontalAlignment: HorizontalAlignment.Fill
                                        verticalAlignment: VerticalAlignment.Fill
                                        scalingMethod: ScalingMethod.AspectFit
                                        visible: (webViewImage1.loading == 1.0 && !(typeof ListItemData.itemData.Photo === 'undefined'))
                                    }
                                    
                                    ProgressIndicator {
                                        value: webViewImage1.loading
                                        horizontalAlignment: HorizontalAlignment.Center
                                        verticalAlignment: VerticalAlignment.Bottom
                                        visible: ((webViewImage1.loading < 1.0) && !(typeof ListItemData.itemData.Photo === 'undefined'))
                                    }
                                }
  
                                
                            
                            }
                            
                            Container {
                                layout: StackLayout {
                                    orientation: LayoutOrientation.TopToBottom
                                
                                }
                                leftMargin: ui.sdu(4)
                                margin.bottomOffset: ui.sdu(1)
                                
                                verticalAlignment: VerticalAlignment.Center
                                
                                ConnectLabel {
                                    horizontalAlignment: HorizontalAlignment.Left
                                    verticalAlignment: VerticalAlignment.Top
                                    
                                    text: "<b>"+(ListItemData.itemData.LastName + ", " + ListItemData.itemData.FirstName).replace("&", "&amp;")+"</b>";
                                    
                                    textStyle {
                                        base: SystemDefaults.TextStyles.SubtitleText
                                        fontSizeValue: 100
                                        color: Color.create("#37474e")
                                    }
                                }
                                
                                Label {
                                    
                                    verticalAlignment: VerticalAlignment.Center
                                    topMargin: ui.sdu(0.5)
                                    margin.rightOffset: ui.sdu(3.5)
                                    text: getFamilyMemberNames();
                                    textStyle {
                                        base: SystemDefaults.TextStyles.SubtitleText
                                        color: Color.create("#6b8089")
                                    }
                                    
                                    multiline: true
                                }
                                
                                                                  
                            }
                        }
                        
                        
                    }                        
                }                
            
            ]
            function openMap(search) {
                routeInvoker.searchText = _control.encodeQString(search)
                routeInvoker.go();
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
    
    
    }
    
    attachedObjects: [
        RouteMapInvoker {
            id: routeInvoker
        }
    ]                              





}
