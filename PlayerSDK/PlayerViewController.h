//
//  PlayerViewController.h
//  HelloWorld
//
//  Created by Eliza Sapir on 9/11/13.
//
//

/* This class is responsible for player sdk
 in this class we have a player which contains a webview as subview, the webview reflects html5 NativeComponent */

// Copyright (c) 2013 Kaltura, Inc. All rights reserved.
// License: http://corp.kaltura.com/terms-of-use
//

#import <MediaPlayer/MediaPlayer.h>
#import "PlayerSDK/PlayerControlsWebView.h"

typedef enum{
    // Player Content Source Url
    src = 0,
    // Player Current time (Progress Bar)
    currentTime,
    // Player Visibility
    visible,
  #if !(TARGET_IPHONE_SIMULATOR)
        // DRM WideVine Key
        wvServerKey,
    #endif
} Attribute;

// JSCallbackReady Handler Block
typedef void (^JSCallbackReadyHandler)();

@class NativeComponentPlugin;
@class KPEventListener;
@interface PlayerViewController : UIViewController <PlayerControlsWebViewDelegate> {
    MPMoviePlayerController *player;
    NativeComponentPlugin *delegate;
}

@property (nonatomic, strong) IBOutlet PlayerControlsWebView* webView;
@property (nonatomic, strong) MPMoviePlayerController *player;
@property (nonatomic, retain) NativeComponentPlugin *delegate;

@property (readwrite, nonatomic, copy) JSCallbackReadyHandler jsCallbackReadyHandler;

- (void)play;
- (void)pause;
- (void)stop;
- (void)setWebViewURL: (NSString *)iframeUrl;
- (void)stopAndRemovePlayer;
- (void)checkOrientationStatus;
- (void)resizePlayerView: (CGFloat )top right: (CGFloat )right width: (CGFloat )width height: (CGFloat )height;
- (void)openFullScreen: (BOOL)openFullScreen;
- (void)checkDeviceStatus;

// Kaltura Player External API
- (void)registerJSCallbackReady: (JSCallbackReadyHandler)handler;
- (void)addKPlayerEventListener: (NSString *)name forListener: (KPEventListener *)listener;
- (void)removeKPlayerEventListenerWithEventName: (NSString *)name forListenerName: (NSString *)listenerName;
- (void)asyncEvaluate: (NSString *)expression forListener: (KPEventListener *)listener;
- (void)sendNotification: (NSString*)notificationName andNotificationBody: (NSString *)notificationBody;
- (void)setKDPAttribute: (NSString*)pluginName propertyName: (NSString*)propertyName value: (NSString*)value;

@end

@interface NSString (EnumParser)

- (Attribute)attributeNameEnumFromString;

@end