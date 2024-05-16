{
    "targets": [
        {
            "target_name": "addon",
            "sources": ["src/addon.cpp"],
            "dependencies": [
                "<!(node -p \"require('node-addon-api').targets\"):node_addon_api",
            ]
        }
    ]
}