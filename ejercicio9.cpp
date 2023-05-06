fs::path find_smallest_file(const fs::path& folder_path) {
    fs::path smallest_file;
    uintmax_t smallest_size = std::numeric_limits<uintmax_t>::max();
    for (const auto& entry : fs::directory_iterator(folder_path)) {
        if (entry.is_regular_file()) {
            uintmax_t file_size = entry.file_size();
            if (file_size < smallest_size) {
                smallest_file = entry.path();
                smallest_size = file_size;
            }
        }
    }
    return smallest_file;
}

