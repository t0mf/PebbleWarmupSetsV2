AR = 'arm-none-eabi-ar'
ARFLAGS = 'rcs'
AS = 'arm-none-eabi-gcc'
BINDIR = '/usr/local/bin'
BLOCK_MESSAGE_KEYS = []
BUILD_DIR = 'basalt'
BUILD_TYPE = 'app'
BUNDLE_BIN_DIR = 'basalt'
BUNDLE_NAME = 'PebbleWarmupSetsV2.pbw'
CC = ['arm-none-eabi-gcc']
CCLNK_SRC_F = []
CCLNK_TGT_F = ['-o']
CC_NAME = 'gcc'
CC_SRC_F = []
CC_TGT_F = ['-c', '-o']
CC_VERSION = ('4', '7', '2')
CFLAGS = ['-std=c99', '-mcpu=cortex-m3', '-mthumb', '-ffunction-sections', '-fdata-sections', '-g', '-fPIE', '-Os', '-D_TIME_H_', '-Wall', '-Wextra', '-Werror', '-Wno-unused-parameter', '-Wno-error=unused-function', '-Wno-error=unused-variable']
CFLAGS_MACBUNDLE = ['-fPIC']
CFLAGS_cshlib = ['-fPIC']
CPPPATH_ST = '-I%s'
DEFINES = ['RELEASE', 'PBL_PLATFORM_BASALT', 'PBL_COLOR', 'PBL_RECT', 'PBL_MICROPHONE', 'PBL_SMARTSTRAP', 'PBL_HEALTH', 'PBL_SDK_3']
DEFINES_ST = '-D%s'
DEST_BINFMT = 'elf'
DEST_CPU = 'arm'
DEST_OS = 'darwin'
INCLUDES = ['basalt']
LD = 'arm-none-eabi-ld'
LIBDIR = '/usr/local/lib'
LIBPATH_ST = '-L%s'
LIB_DIR = 'node_modules'
LIB_ST = '-l%s'
LINKFLAGS = ['-mcpu=cortex-m3', '-mthumb', '-Wl,--gc-sections', '-Wl,--warn-common', '-fPIE', '-Os']
LINKFLAGS_MACBUNDLE = ['-bundle', '-undefined', 'dynamic_lookup']
LINKFLAGS_cshlib = ['-shared']
LINKFLAGS_cstlib = ['-Wl,-Bstatic']
LINK_CC = ['arm-none-eabi-gcc']
MESSAGE_KEYS = {u'w20k': 13000, u'w55p': 4000, u'w25p': 7000, u'w2point5p': 10000, u'w45p': 5000, u'w100p': 3000, u'barWeight': 2000, u'w10k': 15000, u'w1point25k': 18000, u'unitSystem': 1000, u'w10p': 8000, u'w35p': 6000, u'w5p': 9000, u'w15k': 14000, u'w2point5k': 17000, u'w5k': 16000, u'w50k': 11000, u'w25k': 12000}
MESSAGE_KEYS_DEFINITION = '/Users/thomasfiveash/Desktop/PebbleWarmupSetsV2/build/src/message_keys.auto.c'
MESSAGE_KEYS_HEADER = '/Users/thomasfiveash/Desktop/PebbleWarmupSetsV2/build/include/message_keys.auto.h'
MESSAGE_KEYS_JSON = '/Users/thomasfiveash/Desktop/PebbleWarmupSetsV2/build/js/message_keys.json'
PEBBLE_SDK_COMMON = '/Users/thomasfiveash/Library/Application Support/Pebble SDK/SDKs/current/sdk-core/pebble/common'
PEBBLE_SDK_PLATFORM = '/Users/thomasfiveash/Library/Application Support/Pebble SDK/SDKs/current/sdk-core/pebble/basalt'
PEBBLE_SDK_ROOT = '/Users/thomasfiveash/Library/Application Support/Pebble SDK/SDKs/current/sdk-core/pebble'
PLATFORM = {'TAGS': ['basalt', 'color', 'rect'], 'ADDITIONAL_TEXT_LINES_FOR_PEBBLE_H': [], 'MAX_APP_BINARY_SIZE': 65536, 'MAX_RESOURCES_SIZE': 1048576, 'MAX_APP_MEMORY_SIZE': 65536, 'MAX_WORKER_MEMORY_SIZE': 10240, 'NAME': 'basalt', 'BUNDLE_BIN_DIR': 'basalt', 'BUILD_DIR': 'basalt', 'MAX_RESOURCES_SIZE_APPSTORE': 262144, 'DEFINES': ['PBL_PLATFORM_BASALT', 'PBL_COLOR', 'PBL_RECT', 'PBL_MICROPHONE', 'PBL_SMARTSTRAP', 'PBL_HEALTH']}
PLATFORM_NAME = 'basalt'
PREFIX = '/usr/local'
PROJECT_INFO = {'appKeys': {u'w20k': 13000, u'w55p': 4000, u'w25p': 7000, u'w2point5p': 10000, u'w45p': 5000, u'w100p': 3000, u'barWeight': 2000, u'w10k': 15000, u'w1point25k': 18000, u'unitSystem': 1000, u'w10p': 8000, u'w35p': 6000, u'w5p': 9000, u'w15k': 14000, u'w2point5k': 17000, u'w5k': 16000, u'w50k': 11000, u'w25k': 12000}, u'sdkVersion': u'3', u'projectType': u'native', u'uuid': u'7d96d084-33fb-4fec-8edf-7f4013e459ab', u'messageKeys': {u'w20k': 13000, u'w55p': 4000, u'w25p': 7000, u'w2point5p': 10000, u'w45p': 5000, u'w100p': 3000, u'barWeight': 2000, u'w10k': 15000, u'w1point25k': 18000, u'unitSystem': 1000, u'w10p': 8000, u'w35p': 6000, u'w5p': 9000, u'w15k': 14000, u'w2point5k': 17000, u'w5k': 16000, u'w50k': 11000, u'w25k': 12000}, 'companyName': u'thomasfiveash', u'enableMultiJS': False, u'targetPlatforms': [u'aplite', u'basalt', u'chalk', u'diorite', u'emery'], u'capabilities': [u'configurable'], 'versionLabel': u'1.0', 'longName': u'Warmup Sets v2', u'displayName': u'Warmup Sets v2', 'shortName': u'Warmup Sets v2', u'watchapp': {u'watchface': False}, u'resources': {u'media': [{u'targetPlatforms': None, u'type': u'bitmap', u'name': u'reset', u'file': u'images/reset'}, {u'targetPlatforms': None, u'type': u'bitmap', u'name': u'plus', u'file': u'images/plus'}, {u'targetPlatforms': None, u'type': u'bitmap', u'name': u'play_reset', u'file': u'images/play_reset'}, {u'targetPlatforms': None, u'type': u'bitmap', u'name': u'play', u'file': u'images/play'}, {u'targetPlatforms': None, u'type': u'bitmap', u'name': u'pause', u'file': u'images/pause'}, {u'targetPlatforms': None, u'type': u'bitmap', u'name': u'minus', u'file': u'images/minus'}, {u'targetPlatforms': None, u'type': u'bitmap', u'name': u'check_mark', u'file': u'images/check_mark'}, {u'targetPlatforms': None, u'type': u'bitmap', u'name': u'5_plus', u'file': u'images/5_plus'}, {u'targetPlatforms': None, u'type': u'bitmap', u'name': u'5_minus', u'file': u'images/5_minus'}, {u'targetPlatforms': None, u'type': u'bitmap', u'name': u'25_plus', u'file': u'images/25_plus'}, {u'targetPlatforms': None, u'type': u'bitmap', u'name': u'25_minus', u'file': u'images/25_minus'}, {u'targetPlatforms': None, u'type': u'bitmap', u'name': u'15_plus', u'file': u'images/15_plus'}, {u'targetPlatforms': None, u'type': u'bitmap', u'name': u'15_minus', u'file': u'images/15_minus'}]}, 'name': u'warmup-sets-v2'}
REQUESTED_PLATFORMS = [u'aplite', u'basalt', u'chalk', u'diorite', u'emery']
RESOURCES_JSON = [{u'targetPlatforms': None, u'type': u'bitmap', u'name': u'reset', u'file': u'images/reset'}, {u'targetPlatforms': None, u'type': u'bitmap', u'name': u'plus', u'file': u'images/plus'}, {u'targetPlatforms': None, u'type': u'bitmap', u'name': u'play_reset', u'file': u'images/play_reset'}, {u'targetPlatforms': None, u'type': u'bitmap', u'name': u'play', u'file': u'images/play'}, {u'targetPlatforms': None, u'type': u'bitmap', u'name': u'pause', u'file': u'images/pause'}, {u'targetPlatforms': None, u'type': u'bitmap', u'name': u'minus', u'file': u'images/minus'}, {u'targetPlatforms': None, u'type': u'bitmap', u'name': u'check_mark', u'file': u'images/check_mark'}, {u'targetPlatforms': None, u'type': u'bitmap', u'name': u'5_plus', u'file': u'images/5_plus'}, {u'targetPlatforms': None, u'type': u'bitmap', u'name': u'5_minus', u'file': u'images/5_minus'}, {u'targetPlatforms': None, u'type': u'bitmap', u'name': u'25_plus', u'file': u'images/25_plus'}, {u'targetPlatforms': None, u'type': u'bitmap', u'name': u'25_minus', u'file': u'images/25_minus'}, {u'targetPlatforms': None, u'type': u'bitmap', u'name': u'15_plus', u'file': u'images/15_plus'}, {u'targetPlatforms': None, u'type': u'bitmap', u'name': u'15_minus', u'file': u'images/15_minus'}]
RPATH_ST = '-Wl,-rpath,%s'
SDK_VERSION_MAJOR = 5
SDK_VERSION_MINOR = 78
SHLIB_MARKER = None
SIZE = 'arm-none-eabi-size'
SONAME_ST = '-Wl,-h,%s'
STLIBPATH_ST = '-L%s'
STLIB_MARKER = None
STLIB_ST = '-l%s'
SUPPORTED_PLATFORMS = ['aplite', 'basalt', 'chalk']
TARGET_PLATFORMS = ['chalk', 'basalt', 'aplite']
TIMESTAMP = 1488134342
cprogram_PATTERN = '%s'
cshlib_PATTERN = 'lib%s.so'
cstlib_PATTERN = 'lib%s.a'
macbundle_PATTERN = '%s.bundle'
