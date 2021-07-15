cd $(dirname $0)

# --- EDIT -------------------------------------------------------------------------------------------------------------

# See below for example usage.
VENDOR_NAME="rpuhalovich"
VENDOR_URL="github.com/rpuhalovich"
VENDOR_EMAIL="reanpuhalovich@gmail.com"
PLUGIN_NAME="VReverb"
PLUGIN_IDENTIFIER="com.rpuhalovich.vreverb"
PLUGIN_CLASSNAME="CVreverb"
PLUGIN_CATEGORY="Reverb"
PLUGIN_BUNDLENAME="vreverbbundle"

# --- DO NOT EDIT ------------------------------------------------------------------------------------------------------

EXTERN_DIR=../extern
VST3PROJGEN_DIR=$(EXTERN_DIR)/vst3projectgenerator

git clone --recursive https://github.com/steinbergmedia/vst3sdk.git $(EXTERN_DIR)/VST3_SDK
git clone --recursive https://github.com/steinbergmedia/vst3projectgenerator.git $(VST3PROJGEN_DIR)

# cmake\
# -DSMTG_VENDOR_NAME_CLI="Test Company"\
# -DSMTG_VENDOR_HOMEPAGE_CLI="https://www.testcompany.com"\
# -DSMTG_VENDOR_EMAIL_CLI="tester@testcompany.com"\
# -DSMTG_PLUGIN_NAME_CLI="TestPlugin"\
# -DSMTG_PREFIX_FOR_FILENAMES_CLI="Test_"\
# -DSMTG_PLUGIN_IDENTIFIER_CLI="com.testcompany.vst3.testplugin"\
# -DSMTG_CMAKE_PROJECT_NAME_CLI="TestPlugin"\
# -DSMTG_VENDOR_NAMESPACE_CLI="TestCompany"\
# -DSMTG_PLUGIN_CLASS_NAME_CLI="CTestPlugin"\
# -DSMTG_PLUGIN_CATEGORY_CLI="TestCategory"\
# -DSMTG_PLUGIN_BUNDLE_NAME_CLI="testpluginbundle"\
# -P GenerateVST3Plugin.cmake

cmake\
 -DSMTG_VENDOR_NAME_CLI=$(VENDOR_NAME)\
 -DSMTG_VENDOR_HOMEPAGE_CLI=$(VENDOR_URL)\
 -DSMTG_VENDOR_EMAIL_CLI=$(VENDOR_EMAIL)\
 -DSMTG_PLUGIN_NAME_CLI=$(PLUGIN_NAME)\
 -DSMTG_CMAKE_PROJECT_NAME_CLI=$(PLUGIN_NAME)\
 -DSMTG_PLUGIN_IDENTIFIER_CLI=$(PLUGIN_IDENTIFIER)\
 -DSMTG_VENDOR_NAMESPACE_CLI=$(VENDOR_NAME)\
 -DSMTG_PLUGIN_CLASS_NAME_CLI=$(PLUGIN_CLASSNAME)\
 -DSMTG_PLUGIN_CATEGORY_CLI=$(PLUGIN_CATEGORY)\
 -DSMTG_PLUGIN_BUNDLE_NAME_CLI=$(PLUGIN_BUNDLENAME)\
 -P $(VST3PROJGEN_DIR)/script/GenerateVST3Plugin.cmake

mv $(VST3PROJGEN_DIR)/script/output/"$(VENDOR_NAME)" $(VST3PROJGEN_DIR)/"$(VENDOR_NAME)"
rm -rf $(VST3PROJGEN_DIR)/script/output/
