cd "$(dirname "$0")"

# --- EDIT -------------------------------------------------------------------------------------------------------------

VENDOR_NAME="example_vendor"
VENDOR_URL="github.com/example_vendor_github"
VENDOR_EMAIL="example_vendor@gmail.com"
PLUGIN_NAME="example_plugin"
PREFIX_FOR_FILENAMES="ex_"
PLUGIN_IDENTIFIER="com.example_vendor.example_plugin"
PLUGIN_CLASSNAME="Cexample_plugin"
PLUGIN_CATEGORY="Reverb"
PLUGIN_BUNDLENAME="example_pluginb_bundle"

# --- DO NOT EDIT ------------------------------------------------------------------------------------------------------

EXTERN_DIR=../extern
VST3PROJGEN_DIR=${EXTERN_DIR}/vst3projectgenerator

SOURCE_DIR=../source
RESOURCE_DIR=../resource

git clone --recursive https://github.com/steinbergmedia/vst3sdk.git ${EXTERN_DIR}/VST3_SDK
git clone --recursive https://github.com/steinbergmedia/vst3projectgenerator.git ${VST3PROJGEN_DIR}

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
# -P ../extern/vst3projectgenerator/script/GenerateVST3Plugin.cmake

rm -rf ${VST3PROJGEN_DIR}/"${PLUGIN_NAME}"

cmake\
 -DSMTG_VENDOR_NAME_CLI=${VENDOR_NAME}\
 -DSMTG_VENDOR_HOMEPAGE_CLI=${VENDOR_URL}\
 -DSMTG_VENDOR_EMAIL_CLI=${VENDOR_EMAIL}\
 -DSMTG_PLUGIN_NAME_CLI=${PLUGIN_NAME}\
 -DSMTG_PREFIX_FOR_FILENAMES_CLI=${PREFIX_FOR_FILENAMES}\
 -DSMTG_CMAKE_PROJECT_NAME_CLI=${PLUGIN_NAME}\
 -DSMTG_PLUGIN_IDENTIFIER_CLI=${PLUGIN_IDENTIFIER}\
 -DSMTG_VENDOR_NAMESPACE_CLI=${VENDOR_NAME}\
 -DSMTG_PLUGIN_CLASS_NAME_CLI=${PLUGIN_CLASSNAME}\
 -DSMTG_PLUGIN_CATEGORY_CLI=${PLUGIN_CATEGORY}\
 -DSMTG_PLUGIN_BUNDLE_NAME_CLI=${PLUGIN_BUNDLENAME}\
 -P ${VST3PROJGEN_DIR}/script/GenerateVST3Plugin.cmake

mkdir -p ${VST3PROJGEN_DIR}/generated_files/
mv ${VST3PROJGEN_DIR}/script/output/"${PLUGIN_NAME}" ${VST3PROJGEN_DIR}/generated_files/"${PLUGIN_NAME}"
rm -rf ${VST3PROJGEN_DIR}/script/output/

read -n1 -p "Copy files to resource/ and scripts/ (WILL DELETE SOURCE FILES (rm source/*) BEFORE COPY)? [y,n]" doit 
echo ""
case $doit in
  y|Y)
    rm -f ${SOURCE_DIR}/*
    cp -f ${VST3PROJGEN_DIR}/generated_files/"${PLUGIN_NAME}"/source/* ${SOURCE_DIR}/
    cp -f ${VST3PROJGEN_DIR}/generated_files/"${PLUGIN_NAME}"/resource/"${PREFIX_FOR_FILENAMES}editor.uidesc" ${RESOURCE_DIR}/
    cp -f ${VST3PROJGEN_DIR}/generated_files/"${PLUGIN_NAME}"/resource/"info.plist" ${RESOURCE_DIR}/
    cp -f ${VST3PROJGEN_DIR}/generated_files/"${PLUGIN_NAME}"/resource/"win32resource.rc" ${RESOURCE_DIR}/
  ;;
esac

echo ""
echo "Be sure to remove any previous/unwanted .uidesc files in resource/"
echo "Happy coding!"
