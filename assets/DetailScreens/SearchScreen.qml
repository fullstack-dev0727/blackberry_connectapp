import my.library 1.0
import bb.platform 1.3
import bb.cascades 1.4
import bb.device 1.4
import bb.system 1.2
import "../custom"

Page {

    Container {

        onCreationCompleted: {
            tfSearch.requestFocus();
            _control.resetSearch();
        }
        
        layout: StackLayout {
            orientation: LayoutOrientation.TopToBottom
        }
        onTouch: {
            _control.onTouchFunc();
        }
        Container { 
            layout: StackLayout {orientation: LayoutOrientation.LeftToRight} 
            leftPadding: ui.sdu(1) 
            rightPadding: ui.sdu(1)
            preferredHeight: ui.sdu(14)
                   
            background:  Color.create("#2d85c2")
            
            ImageView {
                margin.topOffset: ui.sdu(2)     
                margin.bottomOffset: ui.sdu(2)     
                verticalAlignment: VerticalAlignment.Center 
                horizontalAlignment: HorizontalAlignment.Left
                imageSource: "asset:///images/titleicons/icon_search_white.png"
                
                //filterColor: Color.create("#2d85c2") //blue
                margin.leftOffset: ui.sdu(2)
            }
            
            TextField { 
                
                margin.topOffset: ui.sdu(2)     
                margin.bottomOffset: ui.sdu(2)     

                id: tfSearch
                objectName: "tfSearch"
                layoutProperties: StackLayoutProperties {spaceQuota: 6}
                verticalAlignment: VerticalAlignment.Center 
                horizontalAlignment: HorizontalAlignment.Left
                backgroundVisible: false
                
                input.submitKey: SubmitKey.Search
                input.onSubmitted: {
                    if (tfSearch.text.length > 1) {
                        _control.resetSearch();
                        //_control.requestSearch(1, tfSearch.text, null);
                        searchTabs.setSelectedIndex(3);
                    }else 
                        toastInvalidSearch.show();
                
                
                }
                input.flags: TextInputFlag.SpellCheck
                input.submitKeyFocusBehavior: SubmitKeyFocusBehavior.Next;
                
                textStyle.color: Color.White
                hintText: "Enter search term"
                
                onTextChanging: {
                
                }
            
            } 
            
            Container {
                margin.topOffset: ui.sdu(2)     
                margin.bottomOffset: ui.sdu(2)     

                background: Color.Transparent
                verticalAlignment: VerticalAlignment.Center
                horizontalAlignment: HorizontalAlignment.Right
                margin.rightOffset:  ui.sdu(2)
                
                ConnectLabel {
                    text: "Cancel"
                    textStyle.color: Color.White //Color.create("#2d85c2") //blue 
                    verticalAlignment: VerticalAlignment.Center
                    horizontalAlignment: HorizontalAlignment.Right
                }       
                gestureHandlers: [
                    
                    TapHandler {
                        onTapped: {
                            _home.popScreen();
                        
                        }
                    }
                ]   
            }
        
        
        } 

        
        Container {
            visible: (_home.isGlobalSubs())  
                 
              margin.topOffset: ui.sdu(3)
              margin.bottomOffset:  ui.sdu(3)
              margin.leftOffset: ui.sdu(3)
              margin.rightOffset:  ui.sdu(3)
         
              horizontalAlignment: HorizontalAlignment.Fill
         
              
              layout: DockLayout {
                  
              }
                 
              ConnectLabel {
                  text: "Filter by country"
                  textStyle.fontWeight: FontWeight.W400
                  textStyle.color: Color.create("#FF37474F"); //DARKGRAY
                  textStyle.fontSize: FontSize.Small
                  horizontalAlignment: HorizontalAlignment.Left
                  verticalAlignment: VerticalAlignment.Center
              }
              
              ConnectLabel {
                  id: btCountryFilter
                  objectName: "btCountryFilter"
                  textStyle.fontWeight: FontWeight.W400
                  textStyle.fontSize: FontSize.Small
                  verticalAlignment: VerticalAlignment.Center
                  horizontalAlignment: HorizontalAlignment.Right
                  
                  text: "All"
                  
                  
                  onTextChanged: {
                      _control.resetSearch();
                      searchTabs.setSelectedIndex(3);
                  }
                  
              }   
              
              gestureHandlers: [
                  
                  TapHandler {
                      onTapped: {
                          _control.selectCountryFilter();
                      
                      }
                  }
              ]            
        }
        CustomSegmentedControl {
            id: searchTabs
            
            textTab1: "ALL"
            textTab2: "PEOPLE"
            textTab3: "PLACES"
            
            onSelectedIndexChanged: {
                if (selectedIndex == 0 && tfSearch.text.length > 0) {
                    _control.reqSearch(1, tfSearch.text, null);
                } else if (selectedIndex == 1 && tfSearch.text.length > 0) {
                    _control.reqSearch(1, tfSearch.text, "Member");           
                }else if (selectedIndex == 2 && tfSearch.text.length > 0) {
                    _control.reqSearch(1, tfSearch.text, "Locality,Subdivision");           
                } 
            }
        
        }

        
        
        Container {
            background: Color.White
            layout: DockLayout {
                //orientation: LayoutOrientation.TopToBottom
            }
            
            ActivityIndicator {
                id: contentLoadingIndicator
                objectName: "contentLoadingIndicator"
                verticalAlignment: VerticalAlignment.Center
                horizontalAlignment: HorizontalAlignment.Center
                preferredWidth: ui.sdu(10)
                preferredHeight: ui.sdu(10)
                margin.topOffset: ui.sdu(3)
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
                verticalAlignment: VerticalAlignment.Center
                horizontalAlignment: HorizontalAlignment.Center
                margin.topOffset:  ui.sdu(8)

                ConnectLabel {
                    visible: _control.noresults && !contentLoadingIndicator.running
                    verticalAlignment: VerticalAlignment.Center
                    horizontalAlignment: HorizontalAlignment.Center
                    
                    text: "No results found"
                
                }
                
                Container {
                    visible: _control.noresults && !contentLoadingIndicator.running && _control.isRegional
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
                
                
                
                }
            
            }
            
            
            
            
            ListView {
                id: listView
                objectName: "listView"
                
                margin.topOffset: ui.sdu(3)
                
                function itemType(data, indexPath) {
                    if (data.itemData.Type == "Member")   
                            return "people";
                     else 
                            return "local";
                }
                
                function openLocal(selectedItem) {
                    if (selectedItem.itemData.Type == "Locality")
                        _control.openLocality(selectedItem.itemData.Result.Id, selectedItem.itemData.Result.Name)
                    else                         
                        _control.openSubdivision(selectedItem.itemData.Result.Id, selectedItem.itemData.Result.Name);
                }
                 
             
                onTriggered: {
                    var selectedItem = dataModel. data(indexPath);
                    selectedItem.itemData.Type == "Member" ? _control.openHousehold(selectedItem.itemData.Result.HouseholderId, selectedItem.itemData.Result.Household_LastName) : openLocal(selectedItem);
                }
                
                listItemComponents: [
                    ListItemComponent {
                        type: "people"
                        Container {
                            id: mainContainer
                            
                            horizontalAlignment: HorizontalAlignment.Fill
                            
                            layout: DockLayout {}
                            
                            
                            
                            //GET KIDS NAMES
                            function getFamilyMemberNames() {
                                var members = "";
                                
                                if (ListItemData.itemData &&  ListItemData.itemData.Result.ChildrensFirstNames) {
                                    var a = ListItemData.itemData.Result.ChildrensFirstNames
                                    var members = "";
                                    a.forEach(function(entry) {
                                            if (members != "")
                                                members = members + ", ";
                                            members = members + entry;      
                                    });
                                }else if (ListItemData.itemData &&  ListItemData.itemData.Result.FamilyMembers) {
                                        var a = ListItemData.itemData.Result.FamilyMembers
                                        var members = "";
                                        a.forEach(function(entry) {
                                                if (!entry.IsHouseholder && entry.Householder.Id == ListItemData.itemData.Result.Householder.Id) {
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
                                    
                                    minHeight: ui.sdu(25)
                                    minWidth: ui.sdu(25)
                                    preferredHeight: ui.sdu(25)
                                    preferredWidth: ui.sdu(25)
                                    
                                    ImageView {
                                        verticalAlignment: VerticalAlignment.Center
                                        
                                        minHeight: ui.sdu(25)
                                        minWidth: ui.sdu(25)
                                        preferredHeight: ui.sdu(25)
                                        preferredWidth: ui.sdu(25)
                                        scalingMethod: ScalingMethod.AspectFit 
                                        imageSource: "asset:///images/img/placeholder_household.png"
                                        
                                        visible: true
                                    }
                                    
                                    Container {
                                        id: image
                                        margin.topOffset: ui.sdu(1)
                                        margin.bottomOffset: ui.sdu(1)
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
                                            url: image.getUrl((!(typeof ListItemData.itemData === 'undefined') ? ListItemData.itemData : ""), ListItemData.itemData.Photo.Id, ListItemData.itemData.Locality.Id, ListItemData.itemData.Country.Code)
                                            horizontalAlignment: HorizontalAlignment.Fill
                                            verticalAlignment: VerticalAlignment.Fill
                                            minHeight: ui.sdu(25)
                                            minWidth: ui.sdu(25)
                                            preferredHeight: ui.sdu(25)
                                            preferredWidth: ui.sdu(25)
                                            
                                            scalingMethod: ScalingMethod.AspectFit 
                                            
                                            visible: (webViewImage.loading == 1.0 && !(typeof ListItemData.itemData.Result === 'undefined'))
                                        }
                                        ProgressIndicator {
                                            value: webViewImage.loading
                                            horizontalAlignment: HorizontalAlignment.Center
                                            verticalAlignment: VerticalAlignment.Bottom
                                            visible: (webViewImage.loading < 1.0 && ListItemData.itemData && !(typeof ListItemData.itemData.Result.HouseholdPhoto === 'undefined'))
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
                                        textFormat: TextFormat.Html
                                        text: mainContainer.ListItem.view.highlightTerm(ListItemData.itemData.Result.Household_LastName + ", " + ListItemData.itemData.Result.Household_FirstName)

                                        textStyle {
                                            base: SystemDefaults.TextStyles.PrimaryText
                                            fontSizeValue: 100
                                            color: Color.create("#37474e");
                                        }
                                        
                                        

                                    }
                                    
                              
                                    
                                    ConnectLabel {
                                        
                                        verticalAlignment: VerticalAlignment.Center
                                        topMargin: ui.sdu(0.75)
                                        margin.rightOffset: ui.sdu(3.5)
                                        
                                        text: mainContainer.ListItem.view.highlightTerm(getFamilyMemberNames());
                                        textFormat: TextFormat.Html
                                        textStyle {
                                            base: SystemDefaults.TextStyles.SubtitleText
                                            color: Color.Gray
                                            lineHeight: ui.sdu(0.063)
                                        }
                                        
                                        
                                        multiline: true
                                        textFit.mode: LabelTextFitMode.FitToBounds
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
                    },
                    
                    ListItemComponent {
                        type: "local"
                        
                        Container {
                            id: localmainContainer
                            minHeight: ui.du(18)
                            preferredHeight: ui.du(18)
                            horizontalAlignment: HorizontalAlignment.Fill
                            
                            layout: DockLayout {}
                            
                            
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
                                    minWidth: ui.sdu(22)
                                    
                                    horizontalAlignment: HorizontalAlignment.Center
                                    verticalAlignment: VerticalAlignment.Center
                                    margin.bottomOffset: ui.sdu(2)
                                    leftMargin: ui.sdu(4)
                                    
                                    
                                    ImageView {
                                        
                                        horizontalAlignment: HorizontalAlignment.Center
                                        verticalAlignment: VerticalAlignment.Center
                                        
                                        minHeight: ui.sdu(12)
                                        preferredHeight: ui.sdu(12)
                                        minWidth: ui.sdu(12)
                                        preferredWidth: ui.sdu(12)
                                        
                                        //imageSource: 
                                        imageSource: ListItemData.itemData.Result.CountryName ? "asset:///images/buttonimages/ellipse.png" : (ListItemData.itemData.Result.IsMainHall ? "asset:///images/img/subdivision_main_icon.png" : "asset:///images/img/subdivision_icon.png") 
                                        filterColor: ListItemData.itemData.Result.CountryName ? Color.create("#ffFF1744") : null
                                    }
                                    
                                    ConnectLabel {
                                        
                                        horizontalAlignment: HorizontalAlignment.Center
                                        verticalAlignment: VerticalAlignment.Center
                                        
                                        text: ListItemData.itemData.Result.Name[0] 
                                        textStyle.color: Color.White
                                        textStyle.fontWeight: FontWeight.W500
                                        textStyle.fontSize: FontSize.XLarge
                                        visible: ListItemData.itemData.Result.CountryName ? true : false
                                    
                                    }
                                
                                
                                }                
                                
                                Container {
                                    layout: DockLayout {
                                    //    orientation: LayoutOrientation.TopToBottom
                                    }
                                    preferredHeight: ui.sdu(10)
                                    margin.bottomOffset: ui.sdu(1)
                                    leftMargin: ui.sdu(4)

                                    verticalAlignment: VerticalAlignment.Center
                                    horizontalAlignment: HorizontalAlignment.Left
                                    
                                    ConnectLabel {
                                        horizontalAlignment: HorizontalAlignment.Left
                                        verticalAlignment: VerticalAlignment.Top
                                        textFormat: TextFormat.Html
                                        text: localmainContainer.ListItem.view.highlightTerm(ListItemData.itemData.Result.Name) 
                                        textStyle {
                                            base: SystemDefaults.TextStyles.BodyText
                                            color: ListItemData.itemData.Result.IsMainHall ? Color.create("#2d85c2") :  Color.DarkGray  
                                        }
                                    }
                                    
                                    ConnectLabel {
                                        
                                        verticalAlignment: VerticalAlignment.Bottom
                                        horizontalAlignment: HorizontalAlignment.Left
                                        text: ListItemData.itemData.Result.CountryName ? ListItemData.itemData.Result.CountryName : ListItemData.itemData.Result.LocalityName
                                        textStyle {
                                            base: SystemDefaults.TextStyles.SmallText
                                            color: Color.Gray
                                        }
                                        
                                        multiline: true
                                    }
                                }
                            }
                        }  
                        
                    }
                ]
                
                function highlightTerm(str) {
                    function locale(s){
                        var r=s.toLowerCase();
                        r = r.replace(new RegExp("[àáâãäå]", 'g'),"a");
                        r = r.replace(new RegExp("ç", 'g'),"c");
                        r = r.replace(new RegExp("[èéêë]", 'g'),"e");
                        r = r.replace(new RegExp("[ìíîï]", 'g'),"i");
                        r = r.replace(new RegExp("ñ", 'g'),"n");                            
                        r = r.replace(new RegExp("[òóôõö]", 'g'),"o");
                        r = r.replace(new RegExp("[ùúûü]", 'g'),"u");
                        r = r.replace(new RegExp("[ýÿ]", 'g'),"y");
                        return r;
                    }; 
                                        
                    //#2d85c2
                    var  searchTerm = tfSearch.text;
                    
                    var strI = str.toLowerCase();
                    strI = locale(strI);                   
                    var index = strI.toLowerCase().indexOf(searchTerm.toLowerCase());
                    
                    if (index >= 0) {
                        var orig = str.substring(0,index);
                        orig = orig + "<b>" + str.substring(index,index+searchTerm.length) + "</b>";
                        orig = orig + str.substring(index+(searchTerm.length));
                           
                        //var res = str.replace(new RegExp(searchTerm, 'gi'),  "<b>" + orig + "</b>");
                        
                        
                        orig = orig.replace("&", "&amp;");
                        return orig;
                    }else
                        return str;
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
    }//END CONTAINER



    attachedObjects: [
        SystemToast {
            id: toastInvalidSearch
            body: "The search term has to be a text between 2 and 50 characters."
        }

    ]

}
