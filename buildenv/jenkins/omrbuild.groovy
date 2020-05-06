def setBuildStatus(String message, String state, String sha) {
    context = "continuous-integration/eclipse-omr/branch/${params.BUILDSPEC}"
    step([
        $class: "GitHubCommitStatusSetter",
        contextSource: [$class: "ManuallyEnteredCommitContextSource", context: context],
        errorHandlers: [[$class: "ChangingBuildStatusErrorHandler", result: "UNSTABLE"]],
        commitShaSource: [$class: "ManuallyEnteredShaSource", sha: sha ],
        statusBackrefSource: [$class: "ManuallyEnteredBackrefSource", backref: "${BUILD_URL}flowGraphTable/"],
        statusResultSource: [$class: "ConditionalStatusResultSource", results: [[$class: "AnyBuildResult", message: message, state: state]] ]
    ]);
}

defaultCompile = 'make -j4'

class CMake {
    String buildDir = 'build'
    String configureArgs = '-Wdev -C../cmake/caches/Travis.cmake'
    String compileCmd = 'make -j4'
}

class Autotools {
    String buildDir = '.'
    String configureArgs = ''
    String compileCmd = 'make -j4'
}

SPECS = [
    'aix_ppc-64' : [
        'label' : 'aix && ppc',
        'environment' : [
            'PATH+TOOLS=/home/u0020236/tools',
            'CCACHE_CPP2=1'
        ],
        'ccache' : true,
        'buildSystem' : 'cmake',
        'builds' : [
            new CMake(                
                configureArgs: '-Wdev -DCMAKE_C_COMPILER=xlc_r -DCMAKE_CXX_COMPILER=xlC_r -DCMAKE_XL_CreateExportList="/opt/IBM/xlC/13.1.3/bin/CreateExportList -X64" -DOMR_DDR=OFF -C../cmake/caches/Travis.cmake',
                compileCmd: 'export CCACHE_EXTRAFILES="$PWD/omrcfg.h" && make -j8'
            )
        ],
        'test' : true,
        'testArgs' : '',
        'junitPublish' : true
    ],
    'linux_390-64' : [
        'label': 'Linux && 390',
        'environment' : [
            'PATH+CCACHE=/usr/lib/ccache/'
        ],
        'ccache' : true,
        'buildSystem' : 'cmake',
        'builds' : [
            new CMake()
        ],
        'test' : true,
        'testArgs' : '',
        'junitPublish' : true
    ],
    'linux_aarch64' : [
        'label' : 'Linux && x86 && compile:aarch64',
        'environment' : [
            'PATH+CCACHE=/usr/lib/ccache/:/home/jenkins/aarch64/toolchain/bin',
            'PLATFORM=aarch64-linux-gcc',
            'CHOST=aarch64-linux-gnu'
        ],
        'ccache' : true,
        'buildSystem' : 'autoconf',
        'builds' : [
            new Autotools(
                configureArgs: 'SPEC=linux_aarch64'
            )
        ],
        'test' : false
    ],
    'linux_arm' : [
        'label' : 'Linux && x86 && compile:arm',
        'environment' : [
            'PATH+CCACHE=/usr/lib/ccache/:/home/jenkins/arm/toolchain/bin',
            'PLATFORM=arm-linux-gcc',
            'CHOST=arm-linux-gnueabihf'
        ],
        'ccache' : true,
        'buildSystem' : 'autoconf',
        'builds' : [
            new Autotools(
                configureArgs: 'SPEC=linux_arm'
            )
        ],
        'test' : false
    ],
    'linux_ppc-64_le_gcc' : [
        'label' : 'Linux && PPCLE',
        'environment' : [
            'PATH+CCACHE=/usr/lib/ccache/'
        ],
        'ccache' : true,
        'buildSystem' : 'cmake',
        'builds' : [
            new CMake()
        ],
        'test' : true,
        'testArgs' : '',
        'junitPublish' : true
    ],
    'linux_riscv64' : [
        'label' : 'Linux && riscv64',
        'environment' : [
            'PATH+CCACHE=/usr/lib/ccache/'
        ],
        'ccache' : true,
        'buildSystem' : 'cmake',
        'builds' : [
            new CMake()
        ],
        'test' : true,
        'testArgs' : '',
        'junitPublish' : true
    ],
    'linux_riscv64_cross' : [
        'label' : 'Linux && x86 && compile:riscv64',
        'environment' : [
            'PATH+CCACHE=/usr/lib/ccache/'
        ],
        'ccache' : true,
        'buildSystem' : 'cmake',
        'builds' : [
            new CMake(
                buildDir: 'build_native',
                configureArgs: '-DOMR_THREAD=OFF -DOMR_PORT=OFF -DOMR_OMRSIG=OFF -DOMR_GC=OFF -DOMR_FVTEST=OFF',
            ),
            new CMake(
                configureArgs: '-Wdev -C../cmake/caches/Travis.cmake -DCMAKE_FIND_ROOT_PATH=${CROSS_SYSROOT_RISCV64} -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchains/riscv64-linux-cross.cmake -DOMR_TOOLS_IMPORTFILE=../build_native/tools/ImportTools.cmake'
            )
        ],
        'test' : false
    ],
    'linux_x86' : [
        'label' : 'Linux && x86',
        'environment' : [
            'PATH+CCACHE=/usr/lib/ccache/'
        ],
        'ccache' : true,
        'buildSystem' : 'cmake',
        'builds' : [
            new CMake(
                configureArgs: '-Wdev -G Ninja -DOMR_ENV_DATA32=ON -DOMR_DDR=OFF -DOMR_JITBUILDER=OFF -C../cmake/caches/Travis.cmake',
                compileCmd: 'ninja'
            )
        ],
        'test' : true,
        'testArgs' : '',
        'junitPublish' : true
    ],
    'linux_x86-64' : [
        'label' : 'Linux && x86',
        'environment' : [
            'PATH+CCACHE=/usr/lib/ccache/'
        ],
        'ccache' : true,
        'buildSystem' : 'cmake',
        'builds' : [
            new CMake(
                configureArgs: '-Wdev -C../cmake/caches/Travis.cmake -DOMR_OPT_CUDA=ON -DOMR_CUDA_HOME=/usr/local/cuda'
            )
        ],
        'test' : true,
        'testArgs' : '',
        'junitPublish' : true
    ],
    'linux_x86-64_cmprssptrs' : [
        'label' : 'Linux && x86',
        'environment' : [
            'PATH+CCACHE=/usr/lib/ccache/',
            'EXTRA_CONFIGURE_ARGS=--enable-DDR'
        ],
        'ccache' : true,
        'buildSystem' : 'autoconf',
        'builds' : [
            new Autotools(
                configureArgs: 'SPEC=linux_x86-64_cmprssptrs PLATFORM=amd64-linux64-gcc HAS_AUTOCONF=1 all'
            )
        ],
        'test' : true,
        'testArgs' : '',
        'junitPublish' : true
    ],
    'osx_x86-64' : [
        'label' : 'OSX && x86',
        'environment' : [
            'GTEST_FILTER=-*dump_test_create_dump_*:*NumaSetAffinity:*NumaSetAffinitySuspended:*DeathTest*',
            'PATH+CCACHE=/usr/local/opt/ccache/libexec'
        ],
        'ccache' : true,
        'buildSystem' : 'cmake',
        'builds' : [
            new CMake()
        ],
        'test' : true,
        'testArgs' : '',
        'junitPublish' : true
    ],
    'win_x86-64' : [
        'label' : 'Windows && x86',
        'environment' : [
            'GTEST_FILTER=-*dump_test_create_dump_*:*NumaSetAffinity:*NumaSetAffinitySuspended:PortSysinfoTest.sysinfo_test_get_tmp3:ThreadExtendedTest.TestOtherThreadCputime'
        ],
        'ccache' : false,
        'buildSystem' : 'cmake',
        'builds' : [
            new CMake(
                configureArgs: '-Wdev -G "Visual Studio 11 2012 Win64" -C../cmake/caches/AppVeyor.cmake',
                compileCmd: 'cmake --build . -- /m'
            )
        ],
        'test' : true,
        'testArgs' : '-C Debug -j1',
        'junitPublish' : true
    ],
    'zos_390-64' : [
        'label' : 'zOS && 390',
        'environment' : [
        ],
        'ccache' : false,
        'buildSystem' : 'cmake',
        'builds' : [
            new CMake(
                configureArgs: '-Wdev -C../cmake/caches/Travis.cmake -DCMAKE_C_COMPILER=/bin/c89 -DCMAKE_CXX_COMPILER=/bin/xlc -DOMR_DDR=OFF -DOMR_THR_FORK_SUPPORT=0'
            )
        ],
        'test' : true,
        'testArgs' : '',
        'junitPublish' : false
    ]
]

def launch(target) {
spec = SPECS[target]
timestamps {
    timeout(time: 8, unit: 'HOURS') {
        stage('Queue') {
            node(spec.label) {
                ws() {
                    try {
                        timeout(time: 3, unit: 'HOURS') {
                            def tmpDesc = (currentBuild.description) ? currentBuild.description + "<br>" : ""
                            currentBuild.description = tmpDesc + "<a href=${JENKINS_URL}computer/${NODE_NAME}>${NODE_NAME}</a>"
                            /*
                             * ZOS and AIX needs to to add workspace to LIBPATH. Here we add
                             * it to LIBPATH unconditionally on all platforms on the
                             * assumption that other platforms either don't use LIBPATH
                             * (e.g, Linux, macOS).
                             */
                            withEnv(spec.environment + ["LIBPATH+WORKSPACE=${WORKSPACE}", 'GTEST_COLOR=0']) {
                                sh 'printenv'
                                stage('Get Sources') {
                                    if (params.ghprbPullId) {
                                        def gitConfig = scm.getUserRemoteConfigs().get(0)
                                        checkout poll: false,
                                            scm: [$class: 'GitSCM',
                                            branches: [[name: '${sha1}']],
                                            extensions: [[$class: 'CloneOption', honorRefspec: true]],
                                            userRemoteConfigs: [[name: 'origin',
                                                refspec: "+refs/pull/${params.ghprbPullId}/merge:refs/remotes/origin/pr/${params.ghprbPullId}/merge",
                                                url: "${gitConfig.getUrl()}"]
                                            ]
                                        ]
                                    } else {
                                        scmVars = checkout scm
                                        setBuildStatus("In Progress","PENDING","${scmVars.GIT_COMMIT}")
                                    }
                                }
                                stage('Build') {
                                    if (spec.ccache) {
                                        echo 'Output CCACHE stats before running and clear them'
                                        sh 'ccache -s -z'
                                    }

                                    for (build in spec.builds) {
                                        dir("${build.buildDir}") {
                                            echo 'Configure...'
                                            switch (spec.buildSystem) {
                                                case 'cmake':
                                                    sh "cmake ${build.configureArgs} .."
                                                    break
                                                case 'autoconf':
                                                    sh "make -f run_configure.mk OMRGLUE=./example/glue ${build.configureArgs}"
                                                    break
                                                default:
                                                    error("Unknown buildSystem type")
                                            }

                                            echo 'Compile...'
                                            sh "${build.compileCmd}"
                                        }
                                    }

                                    if (spec.ccache) {
                                        echo 'Output CCACHE stats after running'
                                        sh 'ccache -s'
                                    }
                                }
                                stage('Test') {
                                    if (spec.test) {
                                        echo 'Sanity Test...'
                                        switch (spec.buildSystem) {
                                            case 'cmake':
                                                dir("${spec.builds.last().buildDir}") {
                                                    sh "ctest -V ${spec.testArgs}"
                                                    if (spec.junitPublish) {
                                                        junit '**/*results.xml'
                                                    }
                                                }
                                                break
                                            case 'autoconf':
                                                sh "make test ${spec.testArgs}"
                                                break
                                            default:
                                                error("Unknown buildSystem type")
                                        }
                                    } else {
                                        echo "Currently no sanity tests..."
                                    }
                                }
                            }
                        }
                    } finally {
                        if (!params.ghprbPullId) {
                            setBuildStatus("Complete", currentBuild.currentResult, "${scmVars.GIT_COMMIT}")
                        }
                        cleanWs()
                    }
                }
            }
        }
    }
}
}

return this