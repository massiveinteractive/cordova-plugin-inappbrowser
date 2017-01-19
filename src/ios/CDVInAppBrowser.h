/*
 Licensed to the Apache Software Foundation (ASF) under one
 or more contributor license agreements.  See the NOTICE file
 distributed with this work for additional information
 regarding copyright ownership.  The ASF licenses this file
 to you under the Apache License, Version 2.0 (the
 "License"); you may not use this file except in compliance
 with the License.  You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing,
 software distributed under the License is distributed on an
 "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 KIND, either express or implied.  See the License for the
 specific language governing permissions and limitations
 under the License.
 */

#import <Cordova/CDVPlugin.h>
#import <Cordova/CDVInvokedUrlCommand.h>
#import <Cordova/CDVScreenOrientationDelegate.h>
#import "WebViewJavascriptBridge.h"

#define kDefaultToken @"NoHeaderToken"

#ifdef __CORDOVA_4_0_0
#import <Cordova/CDVUIWebViewDelegate.h>
#else
#import <Cordova/CDVWebViewDelegate.h>
#endif

@class CDVInAppBrowserViewController;

@interface CDVInAppBrowser : CDVPlugin {
}

@property (nonatomic, retain) CDVInAppBrowserViewController* inAppBrowserViewController;
@property (nonatomic, copy) NSString* callbackId;
@property (nonatomic, copy) NSRegularExpression *callbackIdPattern;

- (void)open:(CDVInvokedUrlCommand*)command;
- (void)close:(CDVInvokedUrlCommand*)command;
- (void)injectScriptCode:(CDVInvokedUrlCommand*)command;
- (void)show:(CDVInvokedUrlCommand*)command;

@end

@interface CDVInAppBrowserOptions : NSObject {}

@property (nonatomic, assign) BOOL location;
@property (nonatomic, assign) BOOL toolbar;
@property (nonatomic, copy) NSString* closebuttoncaption;
@property (nonatomic, copy) NSString* toolbarposition;
@property (nonatomic, assign) BOOL clearcache;
@property (nonatomic, assign) BOOL clearsessioncache;

@property (nonatomic, copy) NSString* presentationstyle;
@property (nonatomic, copy) NSString* transitionstyle;

@property (nonatomic, assign) BOOL enableviewportscale;
@property (nonatomic, assign) BOOL mediaplaybackrequiresuseraction;
@property (nonatomic, assign) BOOL allowinlinemediaplayback;
@property (nonatomic, assign) BOOL keyboarddisplayrequiresuseraction;
@property (nonatomic, assign) BOOL suppressesincrementalrendering;
@property (nonatomic, assign) BOOL hidden;
@property (nonatomic, assign) BOOL disallowoverscroll;

//PATCH - Color Variables for Navbar
@property (nonatomic, copy) NSString* closebuttoncolor;
@property (nonatomic, assign) BOOL shownavigationbtns;
@property (nonatomic, copy) NSString* toolbarbgcolor;
@property (nonatomic, copy) NSString* gradient1;
@property (nonatomic, copy) NSString* gradient2;
@property (nonatomic, copy) NSString* alphagradient1;
@property (nonatomic, copy) NSString* alphagradient2;
@property (nonatomic, copy) NSString* toolbarcolor;
@property (nonatomic, assign) BOOL hideallbuttons;

//PATCH - Set statusbar light or dark
@property (nonatomic, assign) BOOL statusbarstylelight;

+ (CDVInAppBrowserOptions*)parseOptions:(NSString*)options;

@end

@interface CDVInAppBrowserViewController : UIViewController <UIWebViewDelegate, CDVScreenOrientationDelegate>{
@private
    NSString* _userAgent;
    NSString* _prevUserAgent;
    NSInteger _userAgentLockToken;
    CDVInAppBrowserOptions *_browserOptions;

    UIView *statusBar;
    CAGradientLayer *gradientStatus;
    CAGradientLayer *gradientToolbar;
    
#ifdef __CORDOVA_4_0_0
    CDVUIWebViewDelegate* _webViewDelegate;
#else
    CDVWebViewDelegate* _webViewDelegate;
#endif
}

@property (nonatomic, strong) IBOutlet UIWebView* webView;
@property (nonatomic, strong) IBOutlet UIBarButtonItem* closeButton;
@property (nonatomic, strong) IBOutlet UILabel* addressLabel;
@property (nonatomic, strong) IBOutlet UIBarButtonItem* backButton;
@property (nonatomic, strong) IBOutlet UIBarButtonItem* forwardButton;
@property (nonatomic, strong) IBOutlet UIBarButtonItem* flexibleSpaceButton;
@property (nonatomic, strong) IBOutlet UIBarButtonItem* fixedSpaceButton;
@property (nonatomic, strong) IBOutlet UIActivityIndicatorView* spinner;
@property (nonatomic, strong) IBOutlet UIToolbar* toolbar;
@property (nonatomic, strong) UIView *navBg;

@property (nonatomic, weak) id <CDVScreenOrientationDelegate> orientationDelegate;
@property (nonatomic, weak) CDVInAppBrowser* navigationDelegate;
@property (nonatomic) NSURL* currentURL;
@property (nonatomic, strong) NSString *tokenString;
@property WebViewJavascriptBridge* vcBridge;

@property (nonatomic, strong) NSString *callbackEvent;
@property (nonatomic, strong) CDVInAppBrowser *callbackRef;

-(void)setEventCallback:(NSString *)value andReference:(CDVInAppBrowser*)reference;
-(void)dispatchEvent:(NSString *)event withValue:(id)value;

- (void)close;
- (void)navigateTo:(NSURL*)url;
- (void)showLocationBar:(BOOL)show;
- (void)showToolBar:(BOOL)show : (NSString *) toolbarPosition;
- (void)showNavigationBtns:(BOOL)show; //PATCH - setting forward and back buttons
- (void)setCloseButtonColor:(NSString*)color; //PATCH - setting forward and back buttons
- (void)setCloseButtonTitle:(NSString*)title;
- (void)hideAllBtn:(BOOL)shouldHideAllButtons;
- (void)setToolbarFlatColor:(NSString*)color;
- (void)setToolbarGradientColor:(NSString*)color1 : (NSString *) color2 : (NSString *) alpha1 : (NSString *) alpha2; //PATCH - setting gradient

- (id)initWithUserAgent:(NSString*)userAgent prevUserAgent:(NSString*)prevUserAgent browserOptions: (CDVInAppBrowserOptions*) browserOptions;

@end

@interface CDVInAppBrowserNavigationController : UINavigationController

@property (nonatomic, weak) id <CDVScreenOrientationDelegate> orientationDelegate;

@end

@interface UIColor(HexString)

+ (UIColor *)colorWithHexValue:(uint)hexValue andAlpha:(float)alpha;

@end
