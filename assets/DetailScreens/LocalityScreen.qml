import bb.cascades 1.4
import my.library 1.0
import "../custom"

Page {
    
    actionBarAutoHideBehavior: ActionBarAutoHideBehavior.HideOnScroll
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
        layout: StackLayout {
            orientation: LayoutOrientation.TopToBottom
        }
        horizontalAlignment: HorizontalAlignment.Fill
        verticalAlignment: VerticalAlignment.Fill

        Container {

            background: Color.create("#2d85c2") //blue
            layout: StackLayout {
                orientation: LayoutOrientation.TopToBottom
            }
            topPadding: 20.0
            bottomPadding: 20.0
            horizontalAlignment: HorizontalAlignment.Fill

            ConnectLabel {
                visible: (typeof _control.m_localityModel.Name === 'undefined' ? false : true)
                text: _control.m_localityModel.Name
                textStyle.color: Color.White
                textStyle.fontWeight: FontWeight.W500
                horizontalAlignment: HorizontalAlignment.Center

            }

            ConnectLabel {
                visible: (typeof _control.m_localityModel.Name === 'undefined' ? false : true)
                id: labelInfo
                text: _control.m_localityModel.HouseholdCount + " Households   " + _control.m_localityModel.MemberCount + " Brethren"
                textStyle.color: Color.White
                textStyle.fontSize: FontSize.Small
                horizontalAlignment: HorizontalAlignment.Center

            }
        }

        Container {
            layout: DockLayout {

            }
            horizontalAlignment: HorizontalAlignment.Fill
            verticalAlignment: VerticalAlignment.Fill

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
                    text: "Seems like you don't have access to all Regions. Upgrade your plan to search for members from all around the world"
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
                    text: "Manage Subscription"
                    textStyle.color: Color.create("#2d85c2")
                    textStyle.fontSize: FontSize.Large
                    verticalAlignment: VerticalAlignment.Center
                    horizontalAlignment: HorizontalAlignment.Center

                }

                onTouch: {
                    if (event.touchType == TouchType.Down) {
                        //Do something on down touch - e.g. change background color
                    } else if (event.touchType == TouchType.Up || event.touchType == TouchType.Cancel) {
                        //Users finger has been lifted OR has left the element.
                        onClicked:
                        {
                            _control.manageSubs();
                        }
                    }
                }

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
                    margin.leftOffset: ui.sdu(5)
                    margin.rightOffset: ui.sdu(5)

                    text: _control.errorMessage
                    textStyle {
                        base: SystemDefaults.TextStyles.PrimaryText
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

            //TODO LOCALITY SCREEN

            Container {
                id: rootContainer
                visible: (typeof _control.m_localityModel.Name === 'undefined' ? false : true)

                layout: StackLayout {
                    orientation: LayoutOrientation.TopToBottom
                }

                function reloadCurrentUser() {
                    _home.loadMain();
                }

                onCreationCompleted: {
                    _control.setDefaultLocalityChanged.connect(reloadCurrentUser)
                }

                Container {
                    margin.topOffset: ui.sdu(3)
                    margin.bottomOffset: ui.sdu(3)
                    margin.leftOffset: ui.sdu(3)
                    preferredWidth: maxWidth

                    layout: DockLayout {

                    }

                    Container {
                        layout: StackLayout {
                            orientation: LayoutOrientation.LeftToRight
                        }
                        horizontalAlignment: HorizontalAlignment.Left
                        verticalAlignment: VerticalAlignment.Center

                        ImageView {
                            verticalAlignment: VerticalAlignment.Center
                            imageSource: (_control.defaultLocality == _control.m_localityModel.Id) ? "asset:///images/img/locality_default.png" : "asset:///images/img/locality_ndefault.png"

                            preferredHeight: ui.sdu(5)
                            preferredWidth: ui.sdu(5)

                        }

                        ConnectLabel {
                            text: (_control.defaultLocality == _control.m_localityModel.Id) ? "Default location" : "Set as default locality"
                            textStyle.fontSize: FontSize.Small
                            textStyle.color: Color.create("#3b8ec5")
                            margin.leftOffset: ui.sdu(1)
                            verticalAlignment: VerticalAlignment.Center
                            horizontalAlignment: HorizontalAlignment.Center
                        }

                        gestureHandlers: [
                            TapHandler {
                                onTapped: {
                                    if (! (_control.defaultLocality == _control.m_localityModel.Id)) {
                                        _control.setAsDefaultLocality();
                                    }

                                }
                            }
                        ]

                    }
                    Container {
                        horizontalAlignment: HorizontalAlignment.Right
                        verticalAlignment: VerticalAlignment.Center
                        margin.rightOffset: ui.sdu(3)
                        visible: (_control.oldDefaultLocality > 0)
                        layout: DockLayout {
                        }

                        onTouch: {
                            if (event.touchType == TouchType.Down) {
                                //Do something on down touch - e.g. change background color
                            } else if (event.touchType == TouchType.Up || event.touchType == TouchType.Cancel) {
                                //Users finger has been lifted OR has left the element.
                                onClicked:
                                {
                                    _control.setOldAsDefaultLocality();
                                }
                            }
                        }

                        ImageView {
                            imageSource: "asset:///images/nineslice/rounded.amd"
                            horizontalAlignment: HorizontalAlignment.Fill
                            verticalAlignment: VerticalAlignment.Fill
                            filterColor: Color.create("#1978bb")
                        }

                        ConnectLabel {
                            horizontalAlignment: HorizontalAlignment.Center
                            verticalAlignment: VerticalAlignment.Center
                            margin.rightOffset: ui.sdu(2)
                            margin.leftOffset: ui.sdu(2)
                            textStyle.color: Color.White
                            textStyle.fontSize: FontSize.XSmall
                            textStyle.fontWeight: FontWeight.Bold
                            text: "Undo"

                        }
                    }
                }

                CustomSegmentedControl {
                    id: localityTabs
                    visible: (typeof _control.m_localityModel.Name === 'undefined' ? false : true)

                    textTab1: "HOUSEHOLDS"
                    textTab2: "SUBDIVISIONS"
                    textTab3: "INTERCHANGE"

                    onSelectedIndexChanged: {
                        if (selectedIndex == 0) {
                            _control.requestHouseholds(1);
                            labelInfo.text = _control.m_localityModel.HouseholdCount + " Households   " + _control.m_localityModel.MemberCount + " Brethren";
                        } else if (selectedIndex == 1) {
                            _control.requestSubdivisions(1);
                            labelInfo.text = _control.m_localityModel.SubdivisionsCount + " Subdivisions";
                        } else {
                            _control.requestInterchanges(1);
                            labelInfo.text = "Interchange";
                        }
                    }

                }

                ActivityIndicator {
                    id: contenLoadingIndicator
                    objectName: "contenLoadingIndicator"
                    verticalAlignment: VerticalAlignment.Center
                    horizontalAlignment: HorizontalAlignment.Center
                    preferredWidth: ui.sdu(10)
                    margin.topOffset: ui.sdu(3)
                }

                ListView {
                    id: locality_listview
                    visible: (typeof _control.m_localityModel.Name === 'undefined' ? false : true)
                    objectName: "locality_listview"

                    topPadding: 30

                    function itemType(data, indexPath) {
                        if (localityTabs.selectedIndex == 0)
                            return "0";
                        else if (localityTabs.selectedIndex == 1)
                            return "1";
                        else if (localityTabs.selectedIndex == 2)
                            return "2";
                    }

                    onTriggered: {
                        var selectedItem = dataModel.data(indexPath);
                        if (localityTabs.selectedIndex == 0)
                            _control.openHousehold(selectedItem.itemData.HouseholderId, selectedItem.itemData.LastName);
                        else if (localityTabs.selectedIndex == 1)
                            _control.openSubdivision(selectedItem.itemData.Id, selectedItem.itemData.Name);
                        else if (localityTabs.selectedIndex == 2)
                            _control.openLocality(selectedItem.itemData.InterchangeLocalityId, selectedItem.itemData.InterchangeLocalityName)

                    }

                    listItemComponents: [
                        ListItemComponent {
                            type: "0" //Households

                            Container {
                                id: households
                                preferredWidth: maxWidth
                                preferredHeight: ui.du(22.2)

                                layout: DockLayout {
                                }

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
                                    } else if (ListItemData.itemData && ListItemData.itemData.FamilyMembers) {
                                        var a = ListItemData.itemData.FamilyMembers
                                        var members = "";
                                        a.forEach(function(entry) {
                                                if (! entry.IsHouseholder && entry.Householder.Id == ListItemData.itemData.Householder.Id) {
                                                    if (members != "")
                                                        members = members + ", ";

                                                    members = members + entry.DisplayName;
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

                                        minHeight: ui.sdu(25)
                                        minWidth: ui.sdu(25)
                                        preferredHeight: ui.sdu(25)
                                        preferredWidth: ui.sdu(25)

                                        // The ImageView that shows the loaded image after loading has finished without error
                                        ImageView {
                                            verticalAlignment: VerticalAlignment.Center

                                            minHeight: ui.sdu(25)
                                            minWidth: ui.sdu(25)
                                            preferredHeight: ui.sdu(25)
                                            preferredWidth: ui.sdu(25)

                                            scalingMethod: ScalingMethod.AspectFit
                                            imageSource: "asset:///images/img/placeholder_household.png"

                                            //visible: ((webViewImage.loading < 1.0) || !ListItemData.itemData.Photo.SignedURL340)
                                        }
                                        
                                        Container {
                                            id: imageHousehold
                                            function getUrl(url1, id, localityId, countryCode) {
                                                url1["id"] = id;       
                                                url1["localityId"] = localityId; 
                                                url1["countryCode"] = countryCode;  
                                                return url1; 
                                            }
                                            minHeight: ui.sdu(25)
                                            minWidth: ui.sdu(25)
                                            preferredHeight: ui.sdu(25)
                                            preferredWidth: ui.sdu(25)
                                            layout: DockLayout {
                                            }
                                            
                                            WebImageView {
                                                url: imageHousehold.getUrl((ListItemData.itemData.Photo ? ListItemData.itemData.Photo : ""), ListItemData.itemData.Photo.Id, ListItemData.itemData.Locality.Id, ListItemData.itemData.Country.Code)
                                                horizontalAlignment: HorizontalAlignment.Fill
                                                verticalAlignment: VerticalAlignment.Fill
                                                scalingMethod: ScalingMethod.AspectFit
                                            }
                                            WebImageView {
                                                id: webViewImage
                                                url: imageHousehold.getUrl((ListItemData.itemData.Photo.URL340 ? ListItemData.itemData.Photo.URL340 : ""), ListItemData.itemData.Photo.Id, ListItemData.itemData.Locality.Id, ListItemData.itemData.Country.Code)
                                                horizontalAlignment: HorizontalAlignment.Fill
                                                verticalAlignment: VerticalAlignment.Fill
                                                scalingMethod: ScalingMethod.AspectFit
                                                visible: (webViewImage.loading == 1.0 && ListItemData.itemData && ! (typeof ListItemData.itemData.Photo === 'undefined'))
                                            }

                                            ProgressIndicator {
                                                value: webViewImage.loading
                                                horizontalAlignment: HorizontalAlignment.Center
                                                verticalAlignment: VerticalAlignment.Bottom
                                                visible: ((webViewImage.loading < 1.0) && ListItemData.itemData && ! (typeof ListItemData.itemData.Photo === 'undefined'))
                                            }
                                        }

                                    }

                                    Container {
                                        layout: DockLayout {
                                            //orientation: LayoutOrientation.TopToBottom

                                        }
                                        preferredHeight: ui.sdu(18)
                                        leftMargin: ui.sdu(4)
                                        margin.bottomOffset: ui.sdu(1)

                                        verticalAlignment: VerticalAlignment.Center

                                        ConnectLabel {
                                            horizontalAlignment: HorizontalAlignment.Left
                                            verticalAlignment: VerticalAlignment.Top
                                            text: ListItemData.itemData.LastName + ", " + ListItemData.itemData.FirstName

                                            textStyle {
                                                fontWeight: FontWeight.W500
                                                base: SystemDefaults.TextStyles.BodyText
                                                color: Color.create("#435861")
                                            }
                                        }

                                        Container {
                                            layout: DockLayout {
                                            }
                                            background: Color.create("#f6f6f6")
                                            verticalAlignment: VerticalAlignment.Bottom
                                            horizontalAlignment: HorizontalAlignment.Left
                                            leftPadding: ui.sdu(1)
                                            rightPadding: ui.sdu(1)
                                            ConnectLabel {
                                                text: households.ListItem.view.descriptionLocalCountry()
                                                textStyle {
                                                    base: SystemDefaults.TextStyles.SubtitleText
                                                    color: Color.create("#96a9b4")
                                                }
                                            }
                                        }

                                        ConnectLabel {

                                            verticalAlignment: VerticalAlignment.Center
                                            topMargin: ui.sdu(0.5)
                                            margin.rightOffset: ui.sdu(3.5)
                                            text: getFamilyMemberNames()
                                            textStyle {
                                                base: SystemDefaults.TextStyles.SubtitleText
                                                color: Color.create("#96a9b4")
                                                lineHeight: ui.sdu(0.063)
                                            }

                                            multiline: true
                                        }

                                    }
                                }
                                
                                Divider {
                                    verticalAlignment: VerticalAlignment.Bottom
                                    margin.leftOffset: ui.sdu(2.5)
                                }

                            }
                        },

                        ListItemComponent {
                            type: "1" //Subdivisions

                            Container {
                                preferredHeight: ui.du(18)
                                preferredWidth: maxWidth
                                horizontalAlignment: HorizontalAlignment.Fill

                                layout: StackLayout {
                                    orientation: LayoutOrientation.TopToBottom
                                }

                                Container {
                                    layout: StackLayout {
                                        orientation: LayoutOrientation.LeftToRight
                                    }

                                    horizontalAlignment: HorizontalAlignment.Left
                                    leftPadding: ui.du(2.2)
                                    rightPadding: ui.du(2.2)

                                    // The ImageView that shows the loaded image after loading has finished without error
                                    Container {
                                        layout: DockLayout {

                                        }
                                        preferredWidth: ui.sdu(14)
                                        minWidth: ui.sdu(14)

                                        horizontalAlignment: HorizontalAlignment.Left
                                        verticalAlignment: VerticalAlignment.Center

                                        leftMargin: ui.sdu(2.5)

                                        ImageView {
                                            horizontalAlignment: HorizontalAlignment.Left
                                            verticalAlignment: VerticalAlignment.Center

                                            minHeight: ui.sdu(12)
                                            minWidth: ui.sdu(12)
                                            preferredHeight: ui.sdu(12)
                                            preferredWidth: ui.sdu(12)
                                            scalingMethod: ScalingMethod.AspectFill

                                            imageSource: ListItemData.itemData.IsMainHall ? "asset:///images/img/subdivision_main_icon.png" : "asset:///images/img/subdivision_icon.png"
                                        }

                                        ConnectLabel {

                                            horizontalAlignment: HorizontalAlignment.Left
                                            verticalAlignment: VerticalAlignment.Center

                                            text: ListItemData.itemData.Name[0]
                                            textStyle.color: Color.White
                                            textStyle.fontWeight: FontWeight.W500
                                            textStyle.fontSize: FontSize.XLarge

                                            visible: ListItemData.itemData.CountryName ? true : false

                                        }

                                    }

                                    Container {
                                        layout: StackLayout {
                                            orientation: LayoutOrientation.TopToBottom
                                        }

                                        preferredHeight: ui.sdu(9)
                                        leftMargin: ui.sdu(2)
                                        horizontalAlignment: HorizontalAlignment.Fill
                                        verticalAlignment: VerticalAlignment.Center

                                        ConnectLabel {
                                            horizontalAlignment: HorizontalAlignment.Left
                                            verticalAlignment: VerticalAlignment.Center
                                            text: ListItemData.itemData.Name

                                            textStyle {
                                                fontWeight: FontWeight.W500
                                                base: SystemDefaults.TextStyles.BodyText
                                                color: ListItemData.itemData.IsMainHall ? Color.create("#2d85c2") : Color.create("#435861")
                                            }
                                        }

                                        Container {
                                            layout: DockLayout {
                                            }
                                            background: ListItemData.itemData.IsMainHall ? Color.create("#2d85c2") : Color.create("#f6f6f6")
                                            verticalAlignment: VerticalAlignment.Bottom
                                            horizontalAlignment: HorizontalAlignment.Left
                                            leftPadding: ui.sdu(1)
                                            rightPadding: ui.sdu(1)
                                            ConnectLabel {
                                                text: ListItemData.itemData.HouseholdCount + " households"
                                                textStyle {
                                                    base: SystemDefaults.TextStyles.SubtitleText
                                                    color: ListItemData.itemData.IsMainHall ? Color.White : Color.create("#96a9b4")
                                                }
                                            }
                                        }

                                    }

                                }
                                
                                Divider {
                                    verticalAlignment: VerticalAlignment.Bottom
                                    margin.leftOffset: ui.sdu(2.5)
                                }

                            }

                        },

                        ListItemComponent {
                            type: "2" //Interchanges

                            Container {
                                id: interchanges
                                preferredHeight: ui.du(18)
                                horizontalAlignment: HorizontalAlignment.Fill

                                Divider {
                                    verticalAlignment: VerticalAlignment.Bottom
                                    margin.leftOffset: ui.sdu(3)
                                }

                                layout: DockLayout {
                                }

                                Container {
                                    layout: StackLayout {
                                        orientation: LayoutOrientation.LeftToRight
                                    }

                                    horizontalAlignment: HorizontalAlignment.Left
                                    rightPadding: ui.du(2.2)
                                    leftPadding: ui.du(2.2)

                                    // The ImageView that shows the loaded image after loading has finished without error
                                    Container {
                                        layout: DockLayout {

                                        }
                                        preferredWidth: ui.sdu(27)

                                        horizontalAlignment: HorizontalAlignment.Center
                                        verticalAlignment: VerticalAlignment.Center

                                        leftMargin: ui.sdu(1)

                                        ImageView {

                                            horizontalAlignment: HorizontalAlignment.Center
                                            verticalAlignment: VerticalAlignment.Center

                                            preferredHeight: ui.sdu(12)
                                            preferredWidth: ui.sdu(12)

                                            //imageSource:
                                            imageSource: "asset:///images/buttonimages/ellipse.png"
                                            filterColor: Color.create("#ffFF1744")
                                        }

                                        ConnectLabel {

                                            horizontalAlignment: HorizontalAlignment.Center
                                            verticalAlignment: VerticalAlignment.Center

                                            text: ListItemData.itemData.InterchangeLocalityName[0]
                                            textStyle.color: Color.White
                                            textStyle.fontWeight: FontWeight.W500
                                            textStyle.fontSize: FontSize.XLarge

                                        }

                                    }

                                    Container {
                                        layout: DockLayout {
                                            //    orientation: LayoutOrientation.TopToBottom
                                        }

                                        preferredHeight: ui.sdu(10)
                                        preferredWidth: maxWidth
                                        leftMargin: ui.sdu(3)

                                        verticalAlignment: VerticalAlignment.Center

                                        ConnectLabel {
                                            horizontalAlignment: HorizontalAlignment.Left
                                            verticalAlignment: VerticalAlignment.Top

                                            text: ListItemData.itemData.InterchangeLocalityName
                                            textStyle {
                                                fontWeight: FontWeight.W500
                                                base: SystemDefaults.TextStyles.BodyText
                                                color: Color.create("#435861")
                                            }
                                        }

                                        Container {
                                            layout: DockLayout {
                                            }
                                            background: Color.create("#f6f6f6")
                                            verticalAlignment: VerticalAlignment.Bottom
                                            horizontalAlignment: HorizontalAlignment.Left
                                            leftPadding: ui.sdu(1)
                                            rightPadding: ui.sdu(1)
                                            ConnectLabel {
                                                text: interchanges.ListItem.view.descriptionCountry()
                                                textStyle {
                                                    base: SystemDefaults.TextStyles.SubtitleText
                                                    color: Color.create("#96a9b4")
                                                }
                                            }
                                        }

                                        ImageView {
                                            preferredHeight: ui.sdu(5)
                                            preferredWidth: ui.sdu(5)
                                            margin.rightOffset: ui.sdu(2)
                                            verticalAlignment: VerticalAlignment.Top
                                            horizontalAlignment: HorizontalAlignment.Right
                                            imageSource: "asset:///images/img/location_icon.png"
                                        }

                                        Container {
                                            layout: DockLayout {
                                            }
                                            background: Color.create("#f6f6f6")
                                            verticalAlignment: VerticalAlignment.Bottom
                                            horizontalAlignment: HorizontalAlignment.Right
                                            leftPadding: ui.sdu(1)
                                            rightPadding: ui.sdu(1)
                                            ConnectLabel {
                                                text: ListItemData.itemData.Distance
                                                textStyle {
                                                    base: SystemDefaults.TextStyles.SubtitleText
                                                    color: Color.create("#96a9b4")
                                                }
                                            }
                                        }
                                    }
                                }
                            }

                        }

                    ]

                    function descriptionLocalCountry() {
                        return _control.m_localityModel.Name + ", " + _control.m_localityModel.Country.Name;
                    }
                    
                    function descriptionCountry() {
                        return _control.m_localityModel.Country.Name;
                    }

                }

                ActivityIndicator {
                    id: moreLoadingIndicator
                    objectName: "moreLoadingIndicator"
                    verticalAlignment: VerticalAlignment.Center
                    horizontalAlignment: HorizontalAlignment.Center
                    preferredWidth: ui.sdu(10)
                    margin.topOffset: ui.sdu(3)
                }

            }

        }
    }
}
