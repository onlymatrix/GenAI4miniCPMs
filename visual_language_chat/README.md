# Adapt for mincpmv26
* This example showcases inference of Visual language models (VLMs): [`openbmb/MiniCPM-V-2_6`](https://huggingface.co/openbmb/MiniCPM-V-2_6). The application doesn't have many configuration options to encourage the reader to explore and modify the source code. For example, change the device for inference to GPU. The sample features `ov::genai::VLMPipeline` and runs the simplest deterministic greedy sampling algorithm. There is also a example [python](https://github.com/onlymatrix/miniCPMs/tree/main/miniCPM-V26) which provides an example of Visual-language assistant.

* Note: The OpenVINO GenAI runtime is patched by myself.(Support cancle the inference)

# Download and convert the model

``` sh
conda create -n ov_minicpm python=3.10
conda activate ov_minicpm
pip install -r requirements.txt
python convert_minicpmV26.py -m /path/to/minicpmV26 -o /path/to/minicpmV26_ov
```
# Compile the project using CMake:

```sh
<OpenVINO_2024.5.0 dir>\setupvars.bat
cd visual_language_chat
mkdir build & cd build
cmake -G "Visual Studio 17 2022" -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release --verbose 
```

# Run

<img src="./images/1.jpg" width="50%"></img>

`visual_language_chat /path/to/minicpmV26_ov .\images\1.jpg`  (<font color='red'> ctrl+c to stop the generation/ type 'bye' to exit </font>)

<img src="./images/2.png" width="50%"></img>
