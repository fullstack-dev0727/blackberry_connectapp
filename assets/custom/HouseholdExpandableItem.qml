import bb.cascades 1.4
import my.library 1.0
import bb.platform 1.3
import "../custom"


Container {
    property alias bodyVisible: expandableContainer.visible
    property string collapseImage
    property string expandImage
    
    margin.topOffset: ui.sdu(2)
    margin.bottomOffset: ui.sdu(2)
    
    function openHouseholder(householderId, countryCode) {
        content.ListItem.view.openHouseholder(householderId, countryCode);    
    }
    
    function call(number) {
        content.ListItem.view.call(number);
    }
    
    function livingInHousehold(householder) {
        return content.ListItem.view.livingInHousehold(householder);
    }
    
    function isHouseholderFather(fathername) {
        return content.ListItem.view.isHouseholderFather(fathername);
    }    
    
    function isHouseholderSpouseMother(mothername) {
        return content.ListItem.view.isHouseholderSpouseMother(mothername);
    }    
    
    function getFormattedDate(dateStr) {
        return dateStr.substring(5,7) + '/' + dateStr.substring(0,4); 
    }
    
    function getMemberNameDescription() {
        var dob = "";
        var desc = "";    
        if (content.ListItem.view.isHouseholder(ListItemData.itemData.Id))
            desc = "<b>" + ListItemData.itemData.FirstName + "</b>";
        else
            desc =  ListItemData.itemData.FirstName;
    
        if (ListItemData.itemData.DateOfBirth)
            desc = desc + " " + getFormattedDate(ListItemData.itemData.DateOfBirth);
        
        if (ListItemData.itemData.IsDeceased)
            desc = desc + " <i>Taken</i> ";
        
        if (!typeof ListItemData.itemData.DeceasedDate === 'undefined')
            desc = desc + ListItemData.itemData.DeceasedDate.substring(5,7) + '/' + ListItemData.itemData.DeceasedDate.substring(0,4); ;
        
        return desc;          
    }
     
    function spouses() {
        var spouses = "";
        for (var i = 0; i < ListItemData.itemData.FormerSpouses.length; i++) {
            var local = "";
            var desc = ListItemData.itemData.FormerSpouses[i].Name;
            
            if (ListItemData.itemData.FormerSpouses[i].LocalityName)
                desc = desc + " (" + ListItemData.itemData.FormerSpouses[i].LocalityName + ")"
                
            if (ListItemData.itemData.FormerSpouses[i].IsDeceased)
                desc = desc + "<i> Taken </i>";

            if (!typeof ListItemData.itemData.FormerSpouses[i].DeceasedDate === 'undefined')
                desc = desc + ListItemData.itemData.FormerSpouses[i].DeceasedDate.substring(5,7) + '/' + ListItemData.itemData.FormerSpouses[i].DeceasedDate.substring(0,4); ;
                
            spouses = spouses +  desc + "\n"            
        }
        
        return spouses
    }
    
    function getMotherLocality() {
        var local = "";
        if (typeof ListItemData.itemData.MothersLocality === 'undefined' || !ListItemData.itemData.MothersLocality) 
            local =  "";
        else 
            local =  " ("  + ListItemData.itemData.MothersLocality + ")"
        
        var desc = "";     
        
        if (ListItemData.itemData.MotherDeceased)
            desc = ListItemData.itemData.MothersName + local + " <i>Taken</i> ";
        else                 
            desc = ListItemData.itemData.MothersName + local;
            
        if (!typeof ListItemData.itemData.MotherDeceasedDate === 'undefined') 
            desc = desc + ListItemData.itemData.MotherDeceasedDate.substring(5,7) + '/' + ListItemData.itemData.MotherDeceasedDate.substring(0,4);   
        
        return desc; 
    
    }
    
    function getFatherLocality() {
        var local = "";
        if (typeof ListItemData.itemData.FathersLocality === 'undefined' || !ListItemData.itemData.FathersLocality) 
            local =  "";
        else 
            local =  " ("  + ListItemData.itemData.FathersLocality + ")"
            
        var desc = "";     
        
        if (ListItemData.itemData.FatherDeceased)
            desc = ListItemData.itemData.FathersName + local + " <i>Taken</i> ";
        else                 
            desc = ListItemData.itemData.FathersName + local;
        
        if (!typeof ListItemData.itemData.FatherDeceasedDate === 'undefined') 
            desc = desc + ListItemData.itemData.FatherDeceasedDate.substring(5,7) + '/' + ListItemData.itemData.FatherDeceasedDate.substring(0,4);   
        
       return desc; 
         
    }
   
    Container {
        margin.leftOffset: ui.sdu(2)

        id: visibleContainer
        objectName: "visibleContainer"
        horizontalAlignment: HorizontalAlignment.Fill
        preferredWidth: maxWidth
        
        background: livingInHousehold(ListItemData.itemData.Householder.Id) ? Color.White : Color.create("#70EBE7E6") 
        
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
                    scalingMethod: ScalingMethod.AspectFill 
                    imageSource: "asset:///images/img/placeholder_household.png"
                    visible: true                  
                }                                
                
                Container {
                    id : root
                    preferredHeight: ui.sdu(15)
                    preferredWidth: ui.sdu(15)
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
                        url: root.getUrl(ListItemData.itemData.PhotoTag.URL, ListItemData.itemData.Photo.Id, ListItemData.itemData.Locality.Id, ListItemData.itemData.Country.Code)
                        horizontalAlignment: HorizontalAlignment.Fill
                        verticalAlignment: VerticalAlignment.Fill
                        scalingMethod: ScalingMethod.AspectFill 
                        visible: (webViewImage.loading == 1.0 && !(typeof ListItemData.itemData.PhotoTag.URL === 'undefined'))
                    }
                    ProgressIndicator {
                        value: webViewImage.loading
                        horizontalAlignment: HorizontalAlignment.Center
                        verticalAlignment: VerticalAlignment.Bottom
                        visible: (webViewImage.loading < 1.0 && !(typeof ListItemData.itemData.PhotoTag.URL === 'undefined'))
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
                        color: Color.DarkGray
                                                
                    }
                    textFormat: TextFormat.Html
                    
                   
                
                }
               
                ConnectLabel {
                    horizontalAlignment: HorizontalAlignment.Left
                    verticalAlignment: VerticalAlignment.Center
                    
                    margin.leftOffset: ui.sdu(1)
                    text: "Married" + " (" + ListItemData.itemData.Country.Name + ")"   
                    visible: !livingInHousehold(ListItemData.itemData.Householder.Id)	
                                            
                    textStyle {
                        base: SystemDefaults.TextStyles.SmallText
                        color: Color.DarkGray
                    }
                    
                  
                
                }
                 
            }
        }
        Container {
            verticalAlignment: VerticalAlignment.Center
            horizontalAlignment: HorizontalAlignment.Right
            
            ImageView {
                id: btnHeader
                imageSource: "asset:///images/tabicons/expand_panel.png"
                preferredHeight: ui.sdu(2)
                preferredWidth: ui.sdu(3)
                horizontalAlignment: HorizontalAlignment.Right
                verticalAlignment: VerticalAlignment.Center
                margin.rightOffset: ui.sdu(5)
                visible: ListItemData.itemData.DateOfBirth || !livingInHousehold(ListItemData.itemData.Householder.Id) || (!motherInfo.visible && !fatherInfo.visible && !mobileInfo.visible && !workInfo.visible && !spouseInfo.visible) ? false: true
                
            }
        }
    
        gestureHandlers: [
            
            TapHandler {
                onTapped: {
                    if (btnHeader.visible) {
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
                    }else if (!livingInHousehold(ListItemData.itemData.Householder.Id)) {
                        //open household
                        openHouseholder(ListItemData.itemData.Householder.Id, ListItemData.itemData.Country.Code);
                    }
                
                }
            }
        ] 
    
    
    
    }
    
    Container {
        id: expandableContainer
        objectName: "expandableContainer"
        background: Color.create("#263238") //Color.create("#FF37474F")
        visible: false
        horizontalAlignment: HorizontalAlignment.Fill
        margin.leftOffset: ui.sdu(2)

        
        Container {
            background: Color.create("#2E3C43")
            layout: StackLayout {
                orientation: LayoutOrientation.LeftToRight
            }
            horizontalAlignment: HorizontalAlignment.Fill
            visible: (typeof ListItemData.itemData.PhotoTag.LastUpdated === 'undefined' ? false: true)   
            
            
            ImageView {
                margin.leftOffset: ui.sdu(3)
                preferredHeight: ui.sdu(5)
                preferredWidth: ui.sdu(5)
                verticalAlignment: VerticalAlignment.Center
                
                imageSource: "asset:///images/img/lastupdated_icon.png"
            }
            
            
            ConnectLabel {
                text: "Last update " + ListItemData.itemData.PhotoTag.LastUpdated
                textStyle.color: Color.LightGray
                textStyle.fontSize: FontSize.Small
                margin.topOffset: ui.sdu(2)
                margin.bottomOffset: ui.sdu(2)
                margin.leftOffset: ui.sdu(1)
                
                verticalAlignment: VerticalAlignment.Center
            
            }
            
        }
        
        Container {
            id: workInfo
            layout: DockLayout {
                
            }
            visible: typeof ListItemData.itemData.WorkPhone === 'undefined' || !ListItemData.itemData.WorkPhone? false: true  
            horizontalAlignment: HorizontalAlignment.Fill
            Container {
                horizontalAlignment: HorizontalAlignment.Fill
                verticalAlignment: VerticalAlignment.Center
                margin.topOffset: ui.sdu(5)
                margin.bottomOffset: ui.sdu(5)
                layout: DockLayout {
                    
                }
                
                ConnectLabel {
                    text: "Work: " + ListItemData.itemData.WorkPhone
                    textStyle.color: Color.White
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
                                call(ListItemData.itemData.WorkPhone)
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
            visible: typeof ListItemData.itemData.MobilePhone === 'undefined' || !ListItemData.itemData.MobilePhone? false: true 
            horizontalAlignment: HorizontalAlignment.Fill
            Container {
                horizontalAlignment: HorizontalAlignment.Fill
                verticalAlignment: VerticalAlignment.Center
                margin.topOffset: ui.sdu(5)
                margin.bottomOffset: ui.sdu(5)
                layout: DockLayout {
                
                }
                
                ConnectLabel {
                    text: "Mobile: " + ListItemData.itemData.MobilePhone
                    textStyle.color: Color.White
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
                               
                                call(ListItemData.itemData.MobilePhone);
                               
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
            visible: !(typeof ListItemData.itemData.FormerSpouses === 'undefined') && ListItemData.itemData.FormerSpouses
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
                    textStyle.color: Color.LightGray
                    textStyle.fontSize: FontSize.Small
                    margin.leftOffset: ui.sdu(3)
                    
                
                }
                
                ConnectLabel {
                    id: spouseName
                    text: spouses();
                    textStyle.color: Color.White
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
            visible: typeof ListItemData.itemData.FathersName === 'undefined' || !ListItemData.itemData.FathersName || isHouseholderFather(ListItemData.itemData.FathersName)? false: true
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
                    textStyle.color: Color.LightGray
                    textStyle.fontSize: FontSize.Small
                    margin.leftOffset: ui.sdu(3)
                    horizontalAlignment: HorizontalAlignment.Left
                    verticalAlignment: VerticalAlignment.Center
                }
                
                ConnectLabel {
                    text: getFatherLocality() 
                    textStyle.color: Color.White
                    margin.leftOffset: ui.sdu(3)                  
                }         
            }
            
            Divider {
                verticalAlignment: VerticalAlignment.Bottom
            
            }
            
            
            gestureHandlers: [
                TapHandler {
                    onTapped: {
                        if (ListItemData.itemData.FatherHouseholderId && !ListItemData.itemData.FatherDeceased) {
                            openHouseholder(ListItemData.itemData.FatherHouseholderId);    
                        }
                    }
                }
            ]
        
        }  
        
        
        Container {
            id: motherInfo
            visible: typeof ListItemData.itemData.MothersName === 'undefined' || !ListItemData.itemData.MothersName || isHouseholderSpouseMother(ListItemData.itemData.MothersName)? false: true
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
                    textStyle.color: Color.LightGray
                    textStyle.fontSize: FontSize.Small
                    margin.leftOffset: ui.sdu(3)
                    horizontalAlignment: HorizontalAlignment.Left
                    verticalAlignment: VerticalAlignment.Center
                }
                
                ConnectLabel {

                    
                    text: getMotherLocality()
                    textStyle.color: Color.White
                    margin.leftOffset: ui.sdu(3)
                    
  
                }         
            }
            
            Divider {
                verticalAlignment: VerticalAlignment.Bottom
            
            }
            
            gestureHandlers: [
                TapHandler {
                    onTapped: {
                        if (ListItemData.itemData.MotherHouseholderId && !ListItemData.itemData.MotherDeceased) {
                            openHouseholder(ListItemData.itemData.MotherHouseholderId);    
                        }
                    }
                }
            ]
            
        
        } 
        
    
    
    }    

}
