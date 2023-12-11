//
//  SolarEngineSDK.h
//  SolarEngineSDK
//
//  Created by MVP on 2022/1/20.
//

#import <Foundation/Foundation.h>
#import <SolarEngineSDK/SEEventConstants.h>
#import <UIKit/UIKit.h>
#import <Webkit/WebKit.h>
#import <SolarEngineSDK/SEConfig.h>

#define SESDKVersion @"1.2.6.0"

NS_ASSUME_NONNULL_BEGIN

typedef void (^SEAttributionCallback)(int code, NSDictionary * _Nullable attributionData);

@class UIView, UIViewController;

@interface SolarEngineSDK : NSObject

/// SolarEngineSDK 单例
+ (nonnull instancetype)sharedInstance;

/// 预初始化 SDK
/// @param appKey  应用 appKey，请联系商务人员获取。不允许空
- (void)preInitWithAppKey:(nonnull NSString *)appKey;


/// 初始化 SDK
/// @param appKey  应用 appKey，请联系商务人员获取。不允许空
/// @param userId 用户 ID，请联系商务人员获取。不允许空
/// @param config 配置信息
- (void)startWithAppKey:(nonnull NSString *)appKey userId:(nonnull NSString *)userId config:(SEConfig *)config;


/// 是否开启 GDPR区域限制（不设置时默认不开启 GDPR区域限制）
/// @param isGDPRArea YES 表示开启，NO 表示关闭（开启后SDK将不获取IDFA、IDFV）
- (void)setGDPRArea:(BOOL)isGDPRArea;

/// 设置预置事件属性
/// @param eventType 事件类型
/// @param properties 事件属性
- (void)setPresetEvent:(SEPresetEventType)eventType withProperties:(NSDictionary*)properties;

/// 设置预置事件属性
/// @param webView  系统回调的WKWebView
/// @param request 系统回调的navigationAction.request
- (BOOL)showUpWebView:(WKWebView *)webView withRequest:(NSURLRequest *)request ;

/*
 code说明如下。
 0: 获取到归因结果，归因结果在attributionData中
 非0为获取归因结果失败，情况如下：
 100: _appKey无效
 101:_distinct_id无效
 102: _distinct_id_type无效
 1001: 网络错误，SDK链接服务端失败
 1002: 当次启动请求超过10次还未获取到归因结果
 1003: 距离上次轮询请求归因结果小于5分钟，请5分钟后再试
 1004: 该用户超过15天未获取到归因结果，此次安装内将不再请求归因结果
 */
/// 设置获取归因结果回调，请在初始化SDK前设置回调
/// 当有归因结果或者获取归因结果失败时回调，error.cod如上描述
- (void)setAttributionCallback:(SEAttributionCallback)Callback;

/// 获取归因结果
/// 如果没有归因结果则返回nil
- (NSDictionary *)getAttributionData;


/// 获取SDK事件基础属性
- (NSDictionary *)getPresetProperties;

#pragma 事件

/// 上报自定义事件
/// @param eventName 事件名称 事件名支持大小写中英文、数字、下划线，不能以下划线开头，长度不超过 40
/// @param properties 事件属性
- (void)track:(NSString *)eventName withProperties:(NSDictionary *)properties;

/// 上报应用内购买事件
/// @param attribute SEIAPEventAttribute 实例
- (void)trackIAPWithAttributes:(SEIAPEventAttribute *)attribute;

/// 上报变现广告展示事件
/// @param attribute  SEAdImpressionEventAttribute 实例
- (void)trackAdImpressionWithAttributes:(SEAdImpressionEventAttribute *)attribute;

/// 上报变现广告点击事件
/// @param attribute  SEAdClickEventAttribute 实例
- (void)trackAdClickWithAttributes:(SEAdClickEventAttribute *)attribute;

/// 上报归因事件
/// @param attribute SEAppAttrEventAttribute 实例
- (void)trackAppAttrWithAttributes:(SEAppAttrEventAttribute *)attribute;

/// 上报注册事件
/// @param attribute  SERegisterEventAttribute 实例
- (void)trackRegisterWithAttributes:(SERegisterEventAttribute *)attribute;

/// 上报登录事件
/// @param attribute  SELoginEventAttribute 实例
- (void)trackLoginWithAttributes:(SELoginEventAttribute *)attribute;

/// 上报订单事件
/// @param attribute  SEOrderEventAttribute 实例
- (void)trackOrderWithAttributes:(SEOrderEventAttribute *)attribute;


/// 上报首次事件
/// @param attribute  请传 SEEventBaseAttribute 的子类，具体的事件EventAttribute
- (void)trackFirstEvent:(SEEventBaseAttribute *)attribute;


/// 上报浏览 App 页面事件
/// @param viewController 视图控制器
/// @param properties 自定义属性
- (void)trackAppViewScreen:(UIViewController *)viewController withProperties:( NSDictionary * _Nullable)properties;

/// 上报元素信息事件
/// @param view 页面元素（视图、控件）
/// @param properties 自定义属性
- (void)trackAppClick:(UIView *)view withProperties:(NSDictionary * _Nullable)properties;

/// 开启记录时长事件（配合 - eventFinish:properties: 方法一起使用 ）
/// @param eventName 事件名 事件名支持大小写中英文、数字、下划线，不能以下划线开头，长度不超过 40
- (void)eventStart:(NSString *)eventName;

/// 结束并上报记录时长事件（配合 - eventStart: 方法一起使用 ）
/// @param eventName 事件名 事件名支持大小写中英文、数字、下划线，不能以下划线开头，长度不超过 40
/// @param properties 自定义属性
- (void)eventFinish:(NSString *)eventName properties:(NSDictionary * _Nullable )properties;

/// 设置自动追踪类型，默认不开启自动追踪
/// @param eventType 枚举类型，
/// SEAutoTrackEventTypeNone: SDK不自动追踪埋点采集;
/// SEAutoTrackEventTypeAppClick: SDK自动采集控件点击
/// SEAutoTrackEventTypeAppViewScreen：SDK自动采集页面浏览
/// SEAutoTrackEventTypeAppClick | SEAutoTrackEventTypeAppViewScreen : SDK同时采集控件点击和页面浏览
- (void)setAutoTrackEventType:(SEAutoTrackEventType)eventType;

/// 忽略某类控件自送追踪
/// @param classList 需要忽略控件的类名，例如:  @[[UIButton class]]
- (void)ignoreAutoTrackAppClickClassList:(NSArray<Class> *)classList;

#pragma 访客 ID

/// 设置访客 ID
/// @param visitorId 访客 ID
- (void)setVisitorID:(nonnull NSString *)visitorId;

/// 获取访客 ID
- (nullable NSString *)visitorID;

#pragma 账户 ID

/// 登录并设置账户 ID
/// @param accountId 账户 ID
- (void)loginWithAccountID:(nonnull NSString *)accountId;

/// 账户 ID
- (NSString *)accountID;

/// 退出登录并清除账户 ID
- (void)logout;

/// 获取 distinctId
- (NSString *)getDistinctId;

#pragma 设置公共事件属性

/// 设置公共事件属性
/// @param properties 自定义属性
- (void)setSuperProperties:(NSDictionary *)properties;

/// 清空指定的公共事件属性的值
/// @param key  公共事件属性key
- (void)unsetSuperProperty:(NSString *)key;

/// 清空公共事件属性
- (void)clearSuperProperties;

#pragma 设置用户属性

/// 用户属性初始化设置。使用本方法上传的属性如果已经存在时不修改原有属性值，如果不存在则会新建
/// @param properties 自定义属性
- (void)userInit:(NSDictionary *)properties;

/// 用户属性更新设置。使用本方法上传的属性如果已经存在时将会覆盖原有的属性值，如果不存在则会新建
/// @param properties 自定义属性
- (void)userUpdate:(NSDictionary *)properties;

/// 用户属性累加操作
/// @param properties 自定义属性（仅对数值类型的 key 进行累加操作）
- (void)userAdd:(NSDictionary *)properties;

/// 重置用户属性。对指定属性进行清空操作
/// @param keys 自定义属性 key 数组
- (void)userUnset:(NSArray<NSString *> *)keys;

/// 追加用户属性
/// @param properties 自定义属性
- (void)userAppend:(NSDictionary *)properties;

/// 删除用户
/// @param deleteType 删除用户的类型，
/// SEUserDeleteTypeByAccountId：通过AccountId删除用户
/// SEUserDeleteTypeByVisitorId：   通过VisitorId删除用户
- (void)userDelete:(SEUserDeleteType)deleteType;


/// 获取SDK版本号
- (NSString *)getSDKVersion;


@end


@interface UIView (SolarEngine)

/// 自定义属性，设置自定义属性后会跟随控件点击自动追踪事件一起上报
@property (nonatomic, copy) NSDictionary *se_customProperties;

@end

@interface UIViewController (SolarEngine)

/// 当前页面是否忽略自动追踪，忽略后当前页面内的所有控件点击自动追踪也将忽略。
@property (nonatomic, assign) BOOL se_ignoreAutoTrack;

/// 自定义属性，设置自定义属性后会跟随页面浏览自动追踪事件一起上报
@property (nonatomic, copy) NSDictionary *se_customProperties;

@end

@protocol SEScreenAutoTracker <NSObject>

@optional

- (NSString *)getScreenUrl;

@end



NS_ASSUME_NONNULL_END
