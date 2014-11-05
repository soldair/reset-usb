{
  "targets": [
    {
      "target_name": "resetusb",
      "sources": [
        "src/resetusb.cpp"
      ],
      "include_dirs"  : [
            "<!(node -e \"require('nan')\")"
      ],
      "cflags": ["-g"]
    }
  ]
}
