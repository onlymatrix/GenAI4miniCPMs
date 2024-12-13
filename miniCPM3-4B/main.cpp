// Copyright (C) 2023-2024 Intel Corporation
// SPDX-License-Identifier: Apache-2.0

#include <openvino/genai/visual_language/pipeline.hpp>

void printMetrics(ov::genai::PerfMetrics& metrics) {
    std::cout << "\n\n" << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Load time: " << metrics.get_load_time() << " ms" << std::endl;
    //  TTFT:Time To First Token
    std::cout << "First Token: " << metrics.get_ttft().mean << " ms" << std::endl;
    // Throughput
    std::cout << "Tokens Per Second: " << metrics.get_throughput().mean << " tokens/s" << std::endl;
    // TPOT
    std::cout << "TPOT: " << metrics.get_tpot().mean << " ms/token " << std::endl;
    std::cout << "Tokenization time: " << metrics.get_tokenization_duration().mean << " ms" << std::endl;
    std::cout << "Detokenization time: " << metrics.get_detokenization_duration().mean << " ms" << std::endl;
    std::cout << "Generate time: " << metrics.get_generate_duration().mean << " ms" << std::endl;
}



int main(int argc, char* argv[]) try {
    if (2 != argc) {
        throw std::runtime_error(std::string{"Usage: "} + argv[0] + " <MODEL_DIR>");
    }
    std::string prompt;
    std::string models_path = argv[1];

    std::string device = "CPU";  // GPU, NPU can be used as well
    ov::genai::LLMPipeline pipe(models_path, device);
    //std::string device = "GPU";  // GPU can be used as well
    ov::AnyMap enable_compile_cache;
    if ("GPU" == device) {
        // Cache compiled models on disk for GPU to save time on the
        // next run. It's not beneficial for CPU.
        enable_compile_cache.insert({ov::cache_dir("vlm_cache")});
    }
    //ov::genai::VLMPipeline pipe(argv[1], device, enable_compile_cache);
    
    ov::genai::GenerationConfig generation_config;
    generation_config.max_new_tokens = 256;
     generation_config.do_sample = true;
     generation_config.top_k = 100;
     generation_config.top_p = 0.8;
     generation_config.temperature = 0.7;
     generation_config.presence_penalty = 1.05;

    std::function<bool(std::string)> streamer = [](std::string word) { 
        std::cout << word << std::flush;
        // Return flag corresponds whether generation should be stopped.
        // false means continue generation.
        return false; 
    };

    pipe.start_chat();
    std::cout << "Question:";
    while (std::getline(std::cin, prompt)) {
        if (prompt == "bye") {
            break;
        }
        ov::genai::DecodedResults res = pipe.generate(prompt, generation_config, streamer);
        ov::genai::PerfMetrics metrics = res.perf_metrics;
        metrics = metrics + res.perf_metrics;
        printMetrics(metrics);
        std::cout << "\n----------\n"
            "Question:";
    }
    pipe.finish_chat();
} catch (const std::exception& error) {
    try {
        std::cerr << error.what() << '\n';
    } catch (const std::ios_base::failure&) {}
    return EXIT_FAILURE;
} catch (...) {
    try {
        std::cerr << "Non-exception object thrown\n";
    } catch (const std::ios_base::failure&) {}
    return EXIT_FAILURE;
}
