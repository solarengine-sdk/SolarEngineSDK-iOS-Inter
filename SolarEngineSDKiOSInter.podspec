#
# Be sure to run `pod lib lint SolarEngineSDKiOSInter.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see https://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
  s.name             = 'SolarEngineSDKiOSInter'
  s.version          = '1.2.5.1'

  s.homepage         = 'https://www.solar-engine.com'
  s.license          =  { :type => "Apache License, Version 2.0" }
  s.author           = { 'solarengine-sdk' => 'sdk@solar-engine.com' }
  s.summary          = 'Official SolarEngineSDK for iOS Inter.'
  s.source           = { :git => 'https://github.com/solarengine-sdk/SolarEngineSDK-iOS-Inter.git', :tag => s.version.to_s }

  s.ios.deployment_target = '11.0'

  s.vendored_frameworks = 'SolarEngineSDKiOSInter/SolarEngineSDK.framework'
  
  s.frameworks = "Security", "CoreTelephony", "AdSupport", "SystemConfiguration", "AdServices", "AppTrackingTransparency"
  s.libraries = "sqlite3"
  s.requires_arc = true
  
  s.pod_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64' }
  s.user_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64' }
  
end
