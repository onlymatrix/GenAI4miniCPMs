# OpenVINO GenAI C++ for mincpmv3-4B

* Model: https://huggingface.co/openbmb/MiniCPM3-4B
* OS: Windows 11
* CPU: Intel(R) Core(TM) Ultra 7 258V
* Note: Using OpenVINO pre-release version. [`openvino_genai_windows_2024.6.0.0rc3_x86_64`](https://storage.openvinotoolkit.org/repositories/openvino_genai/packages/pre-release/2024.6.0.0rc3/openvino_genai_windows_2024.6.0.0rc3_x86_64.zip)


# Download and convert the model 
* In case you do not know how to convert.[`Reference`](https://github.com/onlymatrix/miniCPMs/tree/main/miniCPM3-4B)

``` sh
python convert_minincmp3-4B.py -m /path/to/minicpm3-4b -o /path/to/minicpm3-4b_ov
```
# Compile the project using CMake:
```sh
<openvino_genai_windows_2024.6.0.0rc3_x86_64>\setupvars.bat
cd miniCPM3-4B
mkdir build & cd build
cmake -G "Visual Studio 17 2022" -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release --verbose 
```
<img src="./images/1.png" width="50%"></img>
<img src="./images/2.png" width="50%"></img>

# Run
` miniCPM3-4B.exe /path/to/minicpm3-4b_ov`  (<font color='red'> Runing on iGPU </font>)

<img src="./images/3.png" width="50%"></img>
