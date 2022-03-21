import bb.cascades 1.4
import "custom"
import bb.cascades.maps 1.0
import QtMobility.sensors 1.2
import QtMobilitySubset.location 1.1
import bb.device 1.4
import bb.system 1.2


Container {
    id: mainContainer
    
    horizontalAlignment: HorizontalAlignment.Fill
    
    layout: DockLayout {}
    
    function getUrl(url1, id, localityId, countryCode) {
        url1["id"] = id;       
        url1["localityId"] = localityId; 
        url1["countryCode"] = countryCode;  
        return url1; 
    }
    
    //GET KIDS NAMES
    function getFamilyMemberNames() {
        var members = "";
        var a = ListItemData.itemData.Result.ChildrensFirstNames
        var members = "";
        a.forEach(function(entry) {
                if (members != "")
                    members = members + ", ";
                members = members + entry;      
        });
    
    
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
                id: image
                horizontalAlignment: HorizontalAlignment.Fill
                verticalAlignment: VerticalAlignment.Fill
                layout: DockLayout {
                }
                WebImageView {
                    id: webViewImage
                    url: mainContainer.getUrl((!(typeof ListItemData.itemData.Result.HouseholdPhoto === 'undefined') ? ListItemData.itemData.Result.HouseholdPhoto.SignedURL340 : ""), ListItemData.itemData.Photo.Id, ListItemData.itemData.Locality.Id, ListItemData.itemData.Country.Code)
                    horizontalAlignment: HorizontalAlignment.Fill
                    verticalAlignment: VerticalAlignment.Fill
                    minHeight: ui.sdu(22)
                    minWidth: ui.sdu(22)
                    preferredHeight: ui.sdu(22)
                    preferredWidth: ui.sdu(22)
                    
                    scalingMethod: ScalingMethod.AspectFit 
                    
                    visible: (webViewImage.loading == 1.0 && !(typeof ListItemData.itemData.Result.HouseholdPhoto === 'undefined'))
                }
                ProgressIndicator {
                    value: webViewImage.loading
                    horizontalAlignment: HorizontalAlignment.Center
                    verticalAlignment: VerticalAlignment.Bottom
                    visible: (webViewImage.loading < 1.0 && !(typeof ListItemData.itemData.Result.HouseholdPhoto === 'undefined'))
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
                
                text: ListItemData.itemData.Result.Household_LastName + ", " + ListItemData.itemData.Result.Household_FirstName 
                textStyle {
                    base: SystemDefaults.TextStyles.TitleText
                    color: Color.DarkGray
                }
            }
            
            ConnectLabel {
                
                verticalAlignment: VerticalAlignment.Center
                topMargin: ui.sdu(0.75)
                margin.rightOffset: ui.sdu(3.5)
                text: getFamilyMemberNames();
                textStyle {
                    base: SystemDefaults.TextStyles.SubtitleText
                    color: Color.Gray
                    lineHeight: ui.sdu(0.063)
                }
                
                
                multiline: true
            
            }
            
            
            ConnectLabel {
                margin.leftOffset: ui.sdu(1)
                topMargin: ui.sdu(0.8)
                verticalAlignment: VerticalAlignment.Bottom
                
                
                text: ListItemData.itemData.Result.LocalityName + ", " + ListItemData.itemData.Result.CountryName
                textStyle {
                    base: SystemDefaults.TextStyles.SmallText
                    color: Color.Gray
                }
            }                                    
        }
    }
}