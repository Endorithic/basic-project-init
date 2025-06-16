#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>

bool validate_config() noexcept
{
    // Creates variable to store result
    bool did_exist = true;

    // Gets current path
    std::filesystem::path current_dir = std::filesystem::current_path();

    // Check to see if config directory is present in current directory
    std::filesystem::path config_dir = current_dir / "init-config";
    if (!std::filesystem::exists(config_dir))
    {
        // Config directory not present, create it
        std::filesystem::create_directory(config_dir);
        did_exist = false;
    }

    // Adds source_template file if not already present
    std::filesystem::path source_template_path{ config_dir / "source-template.txt" };
    if (!std::filesystem::exists(source_template_path))
    {
        std::ofstream source_template{ source_template_path };
        if (source_template.is_open())
        {
            source_template.close();
        }
    }

    // Adds clangd_template file it not already present
    std::filesystem::path clangd_template_path{ config_dir / "clangd-template.txt" };
    if (!std::filesystem::exists(clangd_template_path))
    {
        std::ofstream clangd_template{ clangd_template_path };
        if (clangd_template.is_open())
        {
            clangd_template.close();
        }
    }

    return did_exist;
}

void create_project(const std::string& argument) noexcept
{
    // Gets current filepath
    const std::filesystem::path current_dir = std::filesystem::current_path();

    // Makes sure project is not already present
    const std::filesystem::path project_dir = current_dir / argument;
    if (std::filesystem::exists(project_dir))
    {
        std::cout << "Project already exists...\n";
        return;
    }

    // Get configuration path
    std::filesystem::path config_dir = current_dir / "init-config";

    // Project directory does not exist, create it
    std::filesystem::create_directory(project_dir);

    // Create source directory
    std::filesystem::path source_dir = project_dir / "src";
    std::filesystem::create_directory(source_dir);

    // Create include directory
    std::filesystem::path include_dir = project_dir / "include";
    std::filesystem::create_directory(include_dir);

    // Create target directory
    std::filesystem::path target_dir = project_dir / "target";
    std::filesystem::create_directory(target_dir);

    // Create debug and release directories
    std::filesystem::path debug_dir = target_dir / "debug";
    std::filesystem::path release_dir = target_dir / "release";
    std::filesystem::create_directory(debug_dir);
    std::filesystem::create_directory(release_dir);

    // Add base source file
    std::ofstream source_file{ source_dir / (argument + ".cpp") };
    if (source_file.is_open())
    {
        // Write to source file according to "source-template"
        std::ifstream source_template{ config_dir / "source-template.txt" };
        std::string line;
        while (std::getline(source_template, line))
        {
            source_file << line << std::endl;
        }
        source_template.close();
        source_file.close();
    }

    // Add ".clangd" file
    std::ofstream clangd_file{ project_dir / ".clangd" };

    // Add config to ".clangd" file (currently hardcoded)
    if (clangd_file.is_open())
    {
        // Write to .clangd file according to "clangd-template"
        std::ifstream clangd_template{ config_dir / "clangd-template.txt" };
        std::string line;
        while (std::getline(clangd_template, line))
        {
            clangd_file << line << std::endl;
        }
        clangd_template.close();
        clangd_file.close();
    }
}

int main(int argc, const char* argv[])
{
    // Validate config
    if (!validate_config())
    {
        std::cout << "Config directory created in current directory.\n";
        return 1;
    }

    // Get argument if application is run with command line arguments
    if (argc == 2)
    {
        const std::string argument = argv[1];
        create_project(argument);
    }

    // Application was not given command line arguments, prompt user for project name
    else if (argc == 1)
    {
        std::string project_name;
        std::cout << "Enter project name: ";
        std::cin >> project_name;
        create_project(project_name);
    }

    // Applications was given more than one command line argument
    else
    {
        std::cout << "Too many command line arguments...";
        return 1;
    }

    return 0;
}
