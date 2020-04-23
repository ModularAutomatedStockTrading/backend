{
    "targets": [{
        "target_name": "NN_engine",
        "cflags!": [ "-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions" ],
        "sources": [
            "src/nn-training/evolutionary/src/main.cpp",
            "src/nn-training/evolutionary/src/classwrapper.cpp",
            "src/nn-training/evolutionary/src/modelTrainer.cpp",
            "src/nn-training/evolutionary/src/neuralNetwork.cpp",
        ],
        'include_dirs': [
            "<!@(node -p \"require('node-addon-api').include\")"
        ],
        'libraries': [],
        'dependencies': [
            "<!(node -p \"require('node-addon-api').gyp\")"
        ],
        'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    }]
}