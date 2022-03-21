import bb.cascades 1.4
import my.library 1.0
import bb.platform 1.3
import bb.device 1.4
import "../custom"
import bb.system 1.2

Page {

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
        
        layout: DockLayout {

        }
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

        ActivityIndicator {
            id: actLoadingIndicator
            objectName: "actLoadingIndicator"
            verticalAlignment: VerticalAlignment.Center
            horizontalAlignment: HorizontalAlignment.Center
            preferredWidth: 100
            margin.topOffset: 20
        }

        ListView {
            id: locality_listview
            objectName: "members_listview"

            function itemType(data, indexPath) {
                if (indexPath == 0)
                    return "main";
                else if (indexPath == (locality_listview.dataModel.childCount(0) - 2))
                    return "locality";
                else if (indexPath == (locality_listview.dataModel.childCount(0) - 1))
                    return "subdivision";
                else
                    return "item";
            }

            listItemComponents: [
                ListItemComponent {
                    type: "main"

                    Container {
                        id: containerHomeTop

                        Container {

                            function getSize() {
                                var h = displayInfo.physicalSize.height;
                                var w = displayInfo.physicalSize.width;

                                var a = (w / h);
                                a = Math.round(a * 100) / 100;

                                if (a == 0.6) //cover some devices - z10...
                                    return ui.sdu(100);
                                else
                                    return ui.sdu(110);
                            }
                            preferredHeight: getSize()
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
                                            horizontalAlignment: HorizontalAlignment.Fill
                                            verticalAlignment: VerticalAlignment.Fill
                                            layout: DockLayout {
                                            }
                                            id: root
                                            function getUrl(url1, id, localityId, countryCode) {
                                                url1["id"] = id;       
                                                url1["localityId"] = localityId; 
                                                url1["countryCode"] = countryCode;  
                                                return url1; 
                                            }

                                            ScrollView {

                                                id: gestureContainer
                                                scrollViewProperties {
                                                    scrollMode: ScrollMode.Both
                                                }
                                                horizontalAlignment: HorizontalAlignment.Fill
                                                verticalAlignment: VerticalAlignment.Fill

                                                scrollRole: ScrollRole.Main
                                                scrollViewProperties.minContentScale: 1.0
                                                scrollViewProperties.maxContentScale: 8.0
                                                scrollViewProperties.pinchToZoomEnabled: true
                                                scrollViewProperties.overScrollEffectMode: OverScrollEffectMode.Default
                                                Container {
                                                    horizontalAlignment: HorizontalAlignment.Fill
                                                    verticalAlignment: VerticalAlignment.Fill
                                                    layout: DockLayout {
                                                    }
                                                    
                                                WebImageView {
                                                    id: webViewImage
                                                    url: root.getUrl(ListItemData.itemData.Photo.URL340, ListItemData.itemData.Photo.Id, ListItemData.itemData.Locality.Id, ListItemData.itemData.Country.Code)
                                                    horizontalAlignment: HorizontalAlignment.Fill
                                                    verticalAlignment: VerticalAlignment.Fill
                                                    scalingMethod: ScalingMethod.AspectFill
                                                }
                                                WebImageView {
                                                    id: webViewImage2
                                                    postLoadingUrl: root.getUrl(ListItemData.itemData.Photo.URL720, ListItemData.itemData.Photo.Id, ListItemData.itemData.Locality.Id, ListItemData.itemData.Country.Code)
                                                    url: root.getUrl(ListItemData.itemData.Photo.URL340, ListItemData.itemData.Photo.Id, ListItemData.itemData.Locality.Id, ListItemData.itemData.Country.Code)
                                                    horizontalAlignment: HorizontalAlignment.Fill
                                                    verticalAlignment: VerticalAlignment.Fill
                                                    scalingMethod: ScalingMethod.AspectFill
                                                    visible: ((webViewImage2.loading == 1.0) || containerHomeTop.ListItem.view.showHdImage())
                                                }
                                            }

                                            }

                                            ProgressIndicator {
                                                value: webViewImage.loading
                                                horizontalAlignment: HorizontalAlignment.Center
                                                verticalAlignment: VerticalAlignment.Bottom
                                                visible: (webViewImage.loading < 1.0 && ! (typeof ListItemData.itemData.Photo.URL340 === 'undefined'))
                                            }
                                        }
                                        /*
                                         * 
                                         * // The ImageView that shows the loaded image after loading has finished without error
                                         * ImageView {
                                         * id: topImage
                                         * scalingMethod: ScalingMethod.Fill
                                         * horizontalAlignment: HorizontalAlignment.Fill
                                         * verticalAlignment: VerticalAlignment.Fill
                                         * 
                                         * image: ListItemData.image
                                         * visible: !ListItemData.loading && ListItemData.label == ""
                                         * }
                                         */

                                    }

                                }

                                Container {
                                    preferredWidth: maxWidth
                                    horizontalAlignment: HorizontalAlignment.Fill
                                    layout: StackLayout {
                                        orientation: LayoutOrientation.TopToBottom
                                    }

                                    id: mainContent

                                    layoutProperties: StackLayoutProperties {
                                        spaceQuota: 1
                                    }

                                    Container {
                                        layout: StackLayout {
                                            orientation: LayoutOrientation.TopToBottom
                                        }
                                        preferredWidth: maxWidth
                                        margin.topOffset: ui.sdu(10)
                                        margin.bottomOffset: ui.sdu(8)
                                        margin.leftOffset: ui.sdu(1)
                                        margin.rightOffset: ui.sdu(1)
                                        verticalAlignment: VerticalAlignment.Center
                                        horizontalAlignment: HorizontalAlignment.Fill

                                        ConnectLabel {
                                            horizontalAlignment: HorizontalAlignment.Center
                                            textStyle.fontSize: FontSize.Large
                                            textStyle.color: Color.create("#FF37474F")
                                            textStyle.fontWeight: FontWeight.W500
                                            text: ListItemData.itemData.LastName + ", " + ListItemData.itemData.FirstName //+ "  " + _control.m_subdivisionModel.HouseholdCount + " households  " + _control.m_subdivisionModel.MemberCount + " brethren"
                                            multiline: true
                                        }

                                        ConnectLabel {
                                            function formatAddress(address) {
                                                var text = address.replace(/[\r\n]+/g, " ");
                                                return text;
                                            }

                                            horizontalAlignment: HorizontalAlignment.Center
                                            textStyle.fontSize: FontSize.Small
                                            textStyle.textAlign: TextAlign.Center
                                            text: formatAddress(ListItemData.itemData.FormattedAddress)
                                            textStyle.color: Color.create("#FF90A4AE")

                                            multiline: true
                                            autoSize.maxLineCount: 2

                                        }

                                    }

                                    Container {
                                        layout: StackLayout {
                                            orientation: LayoutOrientation.TopToBottom
                                        }

                                        horizontalAlignment: HorizontalAlignment.Fill
                                        verticalAlignment: VerticalAlignment.Bottom

                                        Container {
                                            layout: DockLayout {
                                            }
                                            background: Color.create("#fbfbfb")
                                            Divider {
                                                verticalAlignment: VerticalAlignment.Top
                                            }
                                            Divider {
                                                verticalAlignment: VerticalAlignment.Bottom
                                            }

                                            Container {
                                                id: toolbar

                                                layout: StackLayout {
                                                    orientation: LayoutOrientation.LeftToRight

                                                }
                                                preferredHeight: ui.sdu(15)
                                                preferredWidth: maxWidth
                                                horizontalAlignment: HorizontalAlignment.Fill
                                                verticalAlignment: VerticalAlignment.Bottom

                                                Container {
                                                    layout: DockLayout {

                                                    }
                                                    horizontalAlignment: HorizontalAlignment.Fill
                                                    verticalAlignment: VerticalAlignment.Fill
                                                    layoutProperties: StackLayoutProperties {
                                                        spaceQuota: 1
                                                    }

                                                    ImageView {
                                                        verticalAlignment: VerticalAlignment.Center
                                                        imageSource: (ListItemData.itemData.HomePhone ? "asset:///images/tabicons/household_call_ic.png" : "asset:///images/tabicons/household_call_ic_disabled.png")
                                                        preferredHeight: ui.sdu(5)
                                                        preferredWidth: ui.sdu(6)

                                                        horizontalAlignment: HorizontalAlignment.Center
                                                    }

                                                    Container { //vertical line
                                                        minHeight: 0
                                                        maxHeight: Infinity
                                                        preferredHeight: 0
                                                        verticalAlignment: VerticalAlignment.Fill

                                                        minWidth: 2
                                                        maxWidth: 2
                                                        preferredWidth: 2
                                                        horizontalAlignment: HorizontalAlignment.Right

                                                        background: Color.LightGray

                                                    }

                                                    gestureHandlers: [
                                                        TapHandler {
                                                            onTapped: {
                                                                containerHomeTop.ListItem.view.call(ListItemData.itemData.HomePhone, ListItemData.itemData.FirstName);
                                                            }
                                                        }
                                                    ]

                                                }

                                                Container {
                                                    layout: DockLayout {

                                                    }
                                                    horizontalAlignment: HorizontalAlignment.Fill
                                                    verticalAlignment: VerticalAlignment.Fill

                                                    layoutProperties: StackLayoutProperties {
                                                        spaceQuota: 1
                                                    }

                                                    ImageView {
                                                        accessibility.name: "image"
                                                        verticalAlignment: VerticalAlignment.Center
                                                        imageSource: (ListItemData.itemData.Householder.Email ? "asset:///images/tabicons/household_message_ic.png" : "asset:///images/tabicons/household_message_ic_disabled.png")
                                                        preferredHeight: ui.sdu(4.5)
                                                        preferredWidth: ui.sdu(7)

                                                        horizontalAlignment: HorizontalAlignment.Center
                                                    }

                                                    Container { //vertical line
                                                        minHeight: 0
                                                        maxHeight: Infinity
                                                        preferredHeight: 0
                                                        verticalAlignment: VerticalAlignment.Fill

                                                        minWidth: 2
                                                        maxWidth: 2
                                                        preferredWidth: 2
                                                        horizontalAlignment: HorizontalAlignment.Right

                                                        background: Color.LightGray

                                                    }

                                                    gestureHandlers: [
                                                        TapHandler {
                                                            onTapped: {
                                                                containerHomeTop.ListItem.view.sendMessage(ListItemData.itemData.Householder.Email);

                                                            }
                                                        }
                                                    ]

                                                }

                                                Container {
                                                    layout: DockLayout {

                                                    }
                                                    horizontalAlignment: HorizontalAlignment.Fill
                                                    verticalAlignment: VerticalAlignment.Fill

                                                    layoutProperties: StackLayoutProperties {
                                                        spaceQuota: 1
                                                    }

                                                    ImageView {
                                                        verticalAlignment: VerticalAlignment.Center
                                                        imageSource: "asset:///images/tabicons/household_navigate_ic.png"
                                                        preferredHeight: ui.sdu(5)
                                                        preferredWidth: ui.sdu(4.5)

                                                        horizontalAlignment: HorizontalAlignment.Center
                                                    }

                                                    gestureHandlers: [
                                                        TapHandler {
                                                            onTapped: {
                                                                containerHomeTop.ListItem.view.openMap(ListItemData.itemData.FormattedAddress);
                                                            }
                                                        }
                                                    ]

                                                }

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

                                imageSource: "asset:///images/img/household_icon_nfill.png"
                            }

                            ActivityIndicator {
                                id: contentLoadingIndicator
                                objectName: "contentLoadingIndicator"
                                verticalAlignment: VerticalAlignment.Center
                                horizontalAlignment: HorizontalAlignment.Center
                                preferredWidth: 100
                                margin.topOffset: 20
                            }

                            attachedObjects: [
                                DisplayInfo {
                                    id: displayInfo
                                }

                            ]
                        }

                    }
                },
                ListItemComponent {
                    type: "item" //Members

                    Container {
                        property alias bodyVisible: expandableContainer.visible
                        property string collapseImage
                        property string expandImage
                        id: content

                        margin.bottomOffset: ui.sdu(0.2)

                        //Business logic
                        function getMemberNameDescription() {
                            var dob = "";
                            var desc = "";
                            if (content.ListItem.view.isHouseholder(ListItemData.itemData.Id))
                                desc = "<b>" + ListItemData.itemData.DisplayName + "</b>";
                            else
                                desc = ListItemData.itemData.DisplayName;

                            if (ListItemData.itemData.DateOfBirth)
                                desc = desc + " " + content.ListItem.view.getFormattedDate(ListItemData.itemData.DateOfBirth);

                            if (ListItemData.itemData.IsDeceased)
                                desc = desc + " <i>Taken</i> ";

                            if (! (typeof ListItemData.itemData.DeceasedDate === 'undefined'))
                                desc = desc + content.ListItem.view.getFormattedDate(ListItemData.itemData.DeceasedDate);

                            return desc;
                        }

                        function getLivingAwayDescription() {
                            var str = "";

                            if (ListItemData.itemData.Spouse) {
                                str = "Married to " + ListItemData.itemData.Spouse.FirstName + " " + (! (typeof ListItemData.itemData.Spouse.MaidenName === 'undefined') && ListItemData.itemData.Spouse.MaidenName.length > 0 ? ListItemData.itemData.Spouse.MaidenName : ListItemData.itemData.Spouse.LastName);
                                str = str + " (" + ListItemData.itemData.Locality.Name + ")";
                            }

                            return str;
                        }

                        function spouses() {
                            var spouses = "";
                            for (var i = 0; i < ListItemData.itemData.FormerSpouses.length; i ++) {
                                var local = "";
                                var desc = ListItemData.itemData.FormerSpouses[i].Name;

                                if (! (typeof ListItemData.itemData.FormerSpouses[i].MaidenName === 'undefined') && (ListItemData.itemData.FormerSpouses[i].MaidenName.length > 0))
                                    desc = desc + " nee " + ListItemData.itemData.FormerSpouses[i].MaidenName;

                                if (ListItemData.itemData.FormerSpouses[i].LocalityName)
                                    desc = desc + " (" + ListItemData.itemData.FormerSpouses[i].LocalityName + ")"

                                if (ListItemData.itemData.FormerSpouses[i].IsDeceased)
                                    desc = desc + "<i> Taken </i>";

                                if (! (typeof ListItemData.itemData.FormerSpouses[i].DeceasedDate === 'undefined'))
                                    desc = desc + content.ListItem.view.getFormattedDate(ListItemData.itemData.FormerSpouses[i].DeceasedDate);

                                spouses = spouses + desc;

                                if (i + 1 < ListItemData.itemData.FormerSpouses.length) {
                                    spouses = spouses + "\n";
                                }
                            }

                            return spouses
                        }

                        function getMotherLocality() {
                            var local = "";
                            if (typeof ListItemData.itemData.MothersLocality === 'undefined' || ! ListItemData.itemData.MothersLocality)
                                local = "";
                            else
                                local = " (" + ListItemData.itemData.MothersLocality + ")"

                            var desc = ListItemData.itemData.MothersName + local;

                            if (! (typeof ListItemData.itemData.MothersMaidenName === 'undefined') && (ListItemData.itemData.MothersMaidenName.length > 0))
                                desc = desc + " nee " + ListItemData.itemData.MothersMaidenName;

                            if (ListItemData.itemData.MotherDeceased)
                                desc = desc + " <i>Taken</i> ";

                            if (! (typeof ListItemData.itemData.MotherDeceasedDate === 'undefined'))
                                desc = desc + content.ListItem.view.getFormattedDate(ListItemData.itemData.MotherDeceasedDate);

                            return desc;

                        }

                        function getFatherLocality() {
                            var local = "";
                            if (typeof ListItemData.itemData.FathersLocality === 'undefined' || ! ListItemData.itemData.FathersLocality)
                                local = "";
                            else
                                local = " (" + ListItemData.itemData.FathersLocality + ")"

                            var desc = "";

                            if (ListItemData.itemData.FatherDeceased)
                                desc = ListItemData.itemData.FathersName + local + " <i>Taken</i> ";
                            else
                                desc = ListItemData.itemData.FathersName + local;

                            if (! typeof ListItemData.itemData.FatherDeceasedDate === 'undefined')
                                desc = desc + content.ListItem.view.getFormattedDate(ListItemData.itemData.FatherDeceasedDate);

                            return desc;

                        }
                        function getHouseHold() {
                            return  _control.m_householdModel;
                        }
                        Container {
                            leftPadding: ui.sdu(2)

                            id: visibleContainer
                            objectName: "visibleContainer"
                            horizontalAlignment: HorizontalAlignment.Fill
                            preferredWidth: maxWidth

                            background: (!content.ListItem.view.livingInHousehold(ListItemData.itemData.Householder.Id) && ! ListItemData.itemData.Householder.IsDeceased) ? Color.create("#f5f5f5") : Color.White

                            layout: DockLayout {

                            }

                            Container {
                                horizontalAlignment: HorizontalAlignment.Left

                                layout: StackLayout {
                                    orientation: LayoutOrientation.LeftToRight

                                }

                                Container {
                                    layout: DockLayout {

                                    }
                                    ImageView {
                                        preferredHeight: ui.sdu(15)
                                        preferredWidth: ui.sdu(15)
                                        margin.topOffset: ui.sdu(4)
                                        margin.bottomOffset: ui.sdu(4)
                                        scalingMethod: ScalingMethod.AspectFill
                                        imageSource: "asset:///images/img/placeholder_household.png"
                                        visible: true
                                    }

                                    Container {
                                        preferredHeight: ui.sdu(15)
                                        preferredWidth: ui.sdu(15)
                                        margin.topOffset: ui.sdu(4)
                                        margin.bottomOffset: ui.sdu(4)
                                        id: root1
                                        function getUrl1(url1, id, localityId, countryCode) {
                                            url1["id"] = id;       
                                            url1["localityId"] = localityId; 
                                            url1["countryCode"] = countryCode;  
                                            return url1; 
                                        }
                                        layout: DockLayout {
                                        }
                                        WebImageView {
                                            id: webViewImage1
                                            url: root1.getUrl1((ListItemData.itemData.PhotoTag.URL ? ListItemData.itemData.PhotoTag.URL : ""), content.ListItem.view.getPhotoId(), content.ListItem.view.getLocalityId(), content.ListItem.view.getCountryCode())
                                            postLoadingUrl: root1.getUrl1((ListItemData.itemData.PhotoTag.URL ? ListItemData.itemData.PhotoTag.URL : ""), content.ListItem.view.getPhotoId(), content.ListItem.view.getLocalityId(), content.ListItem.view.getCountryCode())
                                            horizontalAlignment: HorizontalAlignment.Fill
                                            verticalAlignment: VerticalAlignment.Fill
                                            scalingMethod: ScalingMethod.AspectFill
                                            // visible: (webViewImage1.loading == 1.0 && ListItemData.itemData && ! (typeof ListItemData.itemData.PhotoTag === 'undefined'))
                                        }
                                        ProgressIndicator {
                                            value: webViewImage1.loading
                                            horizontalAlignment: HorizontalAlignment.Center
                                            verticalAlignment: VerticalAlignment.Bottom
                                            visible: (webViewImage1.loading < 1.0 && ListItemData.itemData && ! (typeof ListItemData.itemData.PhotoTag === 'undefined'))
                                        }
                                    }

                                }

                                Container {
                                    layout: StackLayout {
                                        orientation: LayoutOrientation.TopToBottom
                                    }
                                    verticalAlignment: VerticalAlignment.Center
                                    ConnectLabel {
                                        horizontalAlignment: HorizontalAlignment.Left
                                        verticalAlignment: VerticalAlignment.Center

                                        margin.leftOffset: ui.sdu(1)
                                        text: getMemberNameDescription()

                                        textStyle {
                                            base: SystemDefaults.TextStyles.BodyText
                                            color: Color.create("#3c515a")

                                        }
                                        textFormat: TextFormat.Html

                                    }

                                    ConnectLabel {
                                        horizontalAlignment: HorizontalAlignment.Left
                                        verticalAlignment: VerticalAlignment.Center

                                        margin.leftOffset: ui.sdu(1)
                                        text: getLivingAwayDescription()
                                        visible: ! content.ListItem.view.livingInHousehold(ListItemData.itemData.Householder.Id)

                                        textStyle {
                                            base: SystemDefaults.TextStyles.PrimaryText
                                            fontSizeValue: 75
                                            color: Color.create("#3c515a")
                                        }
                                    }

                                }
                            }
                            Container {
                                verticalAlignment: VerticalAlignment.Center
                                horizontalAlignment: HorizontalAlignment.Right

                                ImageView {

                                    function getImageSource() {
                                        var imgSource = "";
                                        if (!((ListItemData.itemData.DateOfBirth && content.ListItem.view.isHouseholderFather(ListItemData.itemData.FathersName)) || ! (content.ListItem.view.livingInHousehold(ListItemData.itemData.Householder.Id)) || (! motherInfo.visible && ! fatherInfo.visible && ! mobileInfo.visible && ! workInfo.visible && ! spouseInfo.visible))) {
                                            imgSource = "asset:///images/tabicons/expand_panel.png";
                                        } else if (! content.ListItem.view.livingInHousehold(ListItemData.itemData.Householder.Id)) {
                                            imgSource = "asset:///images/tabicons/go_to_icon.png";
                                        }
                                        return imgSource;
                                    }

                                    id: btnHeader
                                    imageSource: getImageSource()
                                    preferredHeight: ui.sdu(6)
                                    preferredWidth: ui.sdu(6)
                                    horizontalAlignment: HorizontalAlignment.Right
                                    verticalAlignment: VerticalAlignment.Center
                                    margin.rightOffset: ui.sdu(5)

                                }
                            }

                            gestureHandlers: [

                                TapHandler {
                                    onTapped: {
                                        if (! ((ListItemData.itemData.DateOfBirth && content.ListItem.view.isHouseholderFather(ListItemData.itemData.FathersName)) || ! (content.ListItem.view.livingInHousehold(ListItemData.itemData.Householder.Id)) || (! motherInfo.visible && ! fatherInfo.visible && ! mobileInfo.visible && ! workInfo.visible && ! spouseInfo.visible))) {
                                            if (bodyVisible) {
                                                expandableContainer.visible = false;
                                                //visibleContainer.background = Color.White
                                                //btnHeader.imageSource = expandImage; //plus and minus image
                                                btnHeader.imageSource = "asset:///images/tabicons/expand_panel.png"

                                            } else {
                                                //visibleContainer.background = Color.create("#263238")
                                                expandableContainer.visible = true;
                                                //btnHeader.imageSource = collapseImage;
                                                btnHeader.imageSource = "asset:///images/tabicons/close_panel.png"
                                            }
                                        } else if (! content.ListItem.view.livingInHousehold(ListItemData.itemData.Householder.Id)) {

                                            //if taken - should open spouse
                                            //open household
                                            if (ListItemData.itemData.Householder.IsDeceased && ListItemData.itemData.Householder.Spouse && ListItemData.itemData.Householder.Spouse.IsHouseholder)
                                                content.ListItem.view.openHouseholder(ListItemData.itemData.Householder.Spouse.Id, ListItemData.itemData.Country.Code);
                                            else if (! ListItemData.itemData.Householder.IsDeceased)
                                                content.ListItem.view.openHouseholder(ListItemData.itemData.Householder.Id, ListItemData.itemData.Country.Code);
                                        }

                                    }
                                }
                            ]

                        }

                        Container {
                            id: expandableContainer
                            objectName: "expandableContainer"
                            background: Color.create("#f5f5f5") //Color.create("#FF37474F")
                            visible: false
                            horizontalAlignment: HorizontalAlignment.Fill

                            Container {
                                id: workInfo
                                layout: DockLayout {

                                }
                                visible: typeof ListItemData.itemData.WorkPhone === 'undefined' || ! ListItemData.itemData.WorkPhone ? false : true
                                horizontalAlignment: HorizontalAlignment.Fill
                                Container {
                                    horizontalAlignment: HorizontalAlignment.Fill
                                    verticalAlignment: VerticalAlignment.Center
                                    margin.topOffset: ui.sdu(5)
                                    margin.bottomOffset: ui.sdu(5)
                                    layout: DockLayout {

                                    }

                                    ConnectLabel {
                                        text: "<b>Work: </b>" + ListItemData.itemData.WorkPhone
                                        textStyle.color: Color.create("#FF37474F")
                                        margin.leftOffset: ui.sdu(3)
                                        horizontalAlignment: HorizontalAlignment.Left
                                        verticalAlignment: VerticalAlignment.Center
                                    }

                                    ImageView {
                                        margin.rightOffset: ui.sdu(3)
                                        preferredHeight: ui.sdu(10)
                                        preferredWidth: ui.sdu(10)
                                        verticalAlignment: VerticalAlignment.Center
                                        horizontalAlignment: HorizontalAlignment.Right

                                        imageSource: "asset:///images/img/call_icon.png"

                                        gestureHandlers: [
                                            TapHandler {
                                                onTapped: {
                                                    content.ListItem.view.call(ListItemData.itemData.WorkPhone, ListItemData.itemData.FirstName)
                                                }
                                            }
                                        ]
                                    }
                                }

                                Divider {
                                    verticalAlignment: VerticalAlignment.Bottom

                                }

                            }

                            Container {
                                id: mobileInfo
                                layout: DockLayout {

                                }
                                visible: typeof ListItemData.itemData.MobilePhone === 'undefined' || ! ListItemData.itemData.MobilePhone ? false : true
                                horizontalAlignment: HorizontalAlignment.Fill
                                Container {
                                    horizontalAlignment: HorizontalAlignment.Fill
                                    verticalAlignment: VerticalAlignment.Center
                                    margin.topOffset: ui.sdu(5)
                                    margin.bottomOffset: ui.sdu(5)
                                    layout: DockLayout {

                                    }

                                    ConnectLabel {
                                        text: "<b>Mobile: </b>" + ListItemData.itemData.MobilePhone
                                        textStyle.color: Color.create("#FF37474F")
                                        margin.leftOffset: ui.sdu(3)
                                        horizontalAlignment: HorizontalAlignment.Left
                                        verticalAlignment: VerticalAlignment.Center
                                    }

                                    ImageView {
                                        margin.rightOffset: ui.sdu(3)
                                        preferredHeight: ui.sdu(10)
                                        preferredWidth: ui.sdu(10)
                                        verticalAlignment: VerticalAlignment.Center
                                        horizontalAlignment: HorizontalAlignment.Right

                                        imageSource: "asset:///images/img/call_icon.png"

                                        gestureHandlers: [
                                            TapHandler {
                                                onTapped: {

                                                    content.ListItem.view.call(ListItemData.itemData.MobilePhone, ListItemData.itemData.FirstName);

                                                }
                                            }
                                        ]
                                    }
                                }

                                Divider {
                                    verticalAlignment: VerticalAlignment.Bottom

                                }

                            }

                            Container {
                                id: spouseInfo
                                visible: ! (typeof ListItemData.itemData.FormerSpouses === 'undefined') && ListItemData.itemData.FormerSpouses
                                layout: DockLayout {

                                }

                                horizontalAlignment: HorizontalAlignment.Fill
                                Container {
                                    horizontalAlignment: HorizontalAlignment.Fill
                                    verticalAlignment: VerticalAlignment.Center
                                    margin.topOffset: ui.sdu(5)
                                    margin.bottomOffset: ui.sdu(5)
                                    layout: StackLayout {
                                        orientation: LayoutOrientation.TopToBottom

                                    }

                                    ConnectLabel {
                                        text: "Previous spouse(s)"
                                        textStyle.color: Color.create("#FF37474F")
                                        textStyle.fontSize: FontSize.Small
                                        margin.leftOffset: ui.sdu(3)

                                    }

                                    ConnectLabel {
                                        id: spouseName
                                        text: spouses()
                                        textStyle.color: Color.create("#FF37474F")
                                        margin.leftOffset: ui.sdu(3)
                                        multiline: true
                                    }

                                }

                                Divider {
                                    verticalAlignment: VerticalAlignment.Bottom

                                }

                            }

                            Container {
                                id: fatherInfo
                                visible: typeof ListItemData.itemData.FathersName === 'undefined' || ! ListItemData.itemData.FathersName || content.ListItem.view.isHouseholderFather(ListItemData.itemData.FathersName) ? false : true
                                layout: DockLayout {

                                }
                                horizontalAlignment: HorizontalAlignment.Fill
                                Container {
                                    horizontalAlignment: HorizontalAlignment.Fill
                                    verticalAlignment: VerticalAlignment.Center
                                    margin.topOffset: ui.sdu(5)
                                    margin.bottomOffset: ui.sdu(5)
                                    layout: StackLayout {
                                        orientation: LayoutOrientation.TopToBottom
                                    }

                                    ConnectLabel {
                                        text: "Father"
                                        textStyle.color: Color.create("#FF37474F")
                                        textStyle.fontSize: FontSize.Small
                                        margin.leftOffset: ui.sdu(3)
                                        horizontalAlignment: HorizontalAlignment.Left
                                        verticalAlignment: VerticalAlignment.Center
                                    }

                                    ConnectLabel {
                                        text: getFatherLocality()
                                        textStyle.color: Color.create("#FF37474F")
                                        margin.leftOffset: ui.sdu(3)
                                    }
                                }

                                Divider {
                                    verticalAlignment: VerticalAlignment.Bottom

                                }

                                gestureHandlers: [
                                    TapHandler {
                                        onTapped: {
                                            if (ListItemData.itemData.FatherHouseholderId && ! ListItemData.itemData.FatherDeceased) {
                                                content.ListItem.view.openHouseholder(ListItemData.itemData.FatherHouseholderId);
                                            }
                                        }
                                    }
                                ]

                            }

                            Container {
                                id: motherInfo
                                visible: typeof ListItemData.itemData.MothersName === 'undefined' || ! ListItemData.itemData.MothersName || content.ListItem.view.isHouseholderSpouseMother(ListItemData.itemData.MothersName) ? false : true
                                layout: DockLayout {

                                }
                                horizontalAlignment: HorizontalAlignment.Fill
                                Container {
                                    horizontalAlignment: HorizontalAlignment.Fill
                                    verticalAlignment: VerticalAlignment.Center
                                    margin.topOffset: ui.sdu(5)
                                    margin.bottomOffset: ui.sdu(5)
                                    layout: StackLayout {
                                        orientation: LayoutOrientation.TopToBottom
                                    }

                                    Label {
                                        text: "Mother"
                                        textStyle.color: Color.create("#FF37474F")
                                        textStyle.fontSize: FontSize.Small
                                        margin.leftOffset: ui.sdu(3)
                                        horizontalAlignment: HorizontalAlignment.Left
                                        verticalAlignment: VerticalAlignment.Center
                                    }

                                    ConnectLabel {

                                        text: getMotherLocality()
                                        textStyle.color: Color.create("#FF37474F")
                                        margin.leftOffset: ui.sdu(3)

                                    }
                                }

                                Divider {
                                    verticalAlignment: VerticalAlignment.Bottom

                                }

                                gestureHandlers: [
                                    TapHandler {
                                        onTapped: {
                                            if (ListItemData.itemData.MotherHouseholderId && ! ListItemData.itemData.MotherDeceased) {
                                                content.ListItem.view.openHouseholder(ListItemData.itemData.MotherHouseholderId);
                                            }
                                        }
                                    }
                                ]

                            }
                            Container {
                                background: Color.White
                                layout: DockLayout {
                                }
                                horizontalAlignment: HorizontalAlignment.Fill
                                visible: (typeof ListItemData.itemData.PhotoTag.LastUpdated === 'undefined' ? false : true)

                                Container {
                                    layout: StackLayout {
                                        orientation: LayoutOrientation.LeftToRight
                                    }
                                    horizontalAlignment: HorizontalAlignment.Center
                                    ImageView {
                                        preferredHeight: ui.sdu(5)
                                        preferredWidth: ui.sdu(5)
                                        verticalAlignment: VerticalAlignment.Center

                                        imageSource: "asset:///images/img/lastupdated_icon.png"
                                    }

                                    ConnectLabel {
                                        text: "Last update " + content.ListItem.view.getFullFormattedDate(ListItemData.itemData.PhotoTag.LastUpdated)
                                        textStyle.color: Color.create("#FF37474F")
                                        textStyle.fontSize: FontSize.XSmall
                                        margin.topOffset: ui.sdu(2)
                                        margin.bottomOffset: ui.sdu(2)
                                        margin.leftOffset: ui.sdu(1)

                                        verticalAlignment: VerticalAlignment.Center

                                    }
                                }

                            }

                        }

                    }

                },
                ListItemComponent {
                    type: "locality" //Locality

                    Container {
                        topPadding: ui.sdu(3)
                        bottomPadding: ui.sdu(3)
                        margin.topOffset: ui.sdu(0.2)
                        preferredWidth: maxWidth
                        id: locality
                        verticalAlignment: VerticalAlignment.Center
                        horizontalAlignment: HorizontalAlignment.Fill
                        layout: StackLayout {
                            orientation: LayoutOrientation.LeftToRight
                        }
                        background: Color.create("#f5f5f5")

                        ImageView {
                            imageSource: "asset:///images/img/location_icon.png"
                            preferredHeight: ui.sdu(8)
                            preferredWidth: ui.sdu(8)
                            minHeight: preferredHeight
                            minWidth: preferredWidth

                            verticalAlignment: VerticalAlignment.Center
                            margin.topOffset: ui.sdu(4)
                            margin.bottomOffset: ui.sdu(2)
                            margin.leftOffset: ui.sdu(3)
                        }

                        ConnectLabel {
                            text: "<b>Locality: </b>" + ListItemData.itemData.Locality.Name
                            margin.leftOffset: ui.sdu(1)
                            multiline: true
                            verticalAlignment: VerticalAlignment.Center
                            textStyle.color: Color.create("#FF37474F")
                            margin.topOffset: ui.sdu(2)
                            margin.bottomOffset: ui.sdu(2)
                        }

                        gestureHandlers: [
                            TapHandler {
                                onTapped: {
                                    locality.ListItem.view.openLocality(ListItemData.itemData.Locality.Id);
                                }
                            }
                        ]

                    }

                },
                ListItemComponent {
                    type: "subdivision" //Locality
                    CustomListItem {
                        dividerVisible: true
                        Container {
                            id: subdivision
                            background: Color.create("#f5f5f5")
                            verticalAlignment: VerticalAlignment.Center
                            horizontalAlignment: HorizontalAlignment.Fill
                            preferredWidth: maxWidth
                            layout: StackLayout {
                                orientation: LayoutOrientation.LeftToRight
                            }
                            topPadding: ui.sdu(3)
                            bottomPadding: ui.sdu(3)

                            ImageView {
                                imageSource: "asset:///images/img/location_icon.png"
                                preferredHeight: ui.sdu(8)
                                preferredWidth: ui.sdu(8)
                                minHeight: preferredHeight
                                minWidth: preferredWidth
                                verticalAlignment: VerticalAlignment.Center
                                margin.topOffset: ui.sdu(4)
                                margin.bottomOffset: ui.sdu(2)
                                margin.leftOffset: ui.sdu(3)
                            }

                            ConnectLabel {
                                text: "<b>Subdivision: </b>" + ListItemData.itemData.Subdivision.Name
                                verticalAlignment: VerticalAlignment.Center
                                margin.topOffset: ui.sdu(2)
                                margin.bottomOffset: ui.sdu(2)
                                textStyle.color: Color.create("#FF37474F")
                                multiline: true
                            }

                            gestureHandlers: [
                                TapHandler {
                                    onTapped: {
                                        subdivision.ListItem.view.openSubdivision(ListItemData.itemData.Subdivision.Id);
                                    }
                                }
                            ]

                        }
                    }

                }
            ]

            function openMap(search) {
                routeInvoker.searchText = _control.encodeQString(search)
                routeInvoker.go();
            }

            function call(number, name) {
                if (typeof number === 'undefined' || number.length === 0) {
                    myQmlToastPhone.show();
                } else {
                    _control.tCallNumber(number, name);
                }
            }

            function sendMessage(email) {
                if (typeof email === 'undefined' || email.length === 0) {
                    myQmlToastEmail.show();
                } else {
                    _control.tSendEmail();
                }
            }

            function livingInHousehold(householder) {
                if (householder === _control.m_householdModel.HouseholderId)
                    return true;
                else
                    return false;

            }

            function openHouseholder(householderId, countryCode) {
                _control.openHouseholder(householderId);
            }

            function showHdImage() {
                return _control.hdImage
            }

            function openLocality(localityId) {
                _control.openLocality(localityId);
            }

            function openSubdivision(subdivisionId) {
                _control.openSubdivision(subdivisionId);
            }

            function getPhotoId() {
                return _control.m_householdModel.Photo.Id;
            }
            function getLocalityId() {
                return _control.m_householdModel.Locality.Id;
            }
            function getCountryCode() {
                return _control.m_householdModel.Country.Code;
            } 
            function isHouseholder(id) {
                if ((id === _control.m_householdModel.Householder.Id) || (_control.m_householdModel.HouseholderSpouse && id === _control.m_householdModel.HouseholderSpouse.Id))
                    return true;
                else
                    return false;
            }
            function isHouseholderFather(fathername) {
                if (fathername === (_control.m_householdModel.Householder.FirstName + " " + _control.m_householdModel.Householder.LastName))
                    return true;
                else
                    return false;
            }

            function isHouseholderSpouseMother(mothername) {
                if ((_control.m_householdModel.HouseholderSpouse && mothername === (_control.m_householdModel.HouseholderSpouse.FirstName + " " + _control.m_householdModel.HouseholderSpouse.LastName)) || (mothername === (_control.m_householdModel.Householder.FirstName + " " + _control.m_householdModel.Householder.LastName)))
                    return true;
                else
                    return false;
            }

            function getFormattedDate(dateStr) {
                return dateStr.substring(8, 10) + '/' + dateStr.substring(5, 7) + '/' + dateStr.substring(0, 4);
            }

            function getFullFormattedDate(dateStr) {
                return dateStr.substring(8, 10) + '/' + dateStr.substring(5, 7) + '/' + dateStr.substring(0, 4);
            }

            function getlocality() {
                if (typeof ListItemData.itemData.MothersLocality === 'undefined' || ListItemData.itemData.MothersLocality == "undefined")
                    return "";
                else
                    return "(" + ListItemData.itemData.MothersLocality + ")"
            }

        }

    }

    attachedObjects: [
        RouteMapInvoker {
            id: routeInvoker
        },
        SystemToast {
            id: myQmlToastPhone
            body: "Sorry. Phone number not available.."
        },
        SystemToast {
            id: myQmlToastEmail
            body: "We are sorry, the householder does not currently have an email address available. Please try phoning instead."
        }

    ]
}
