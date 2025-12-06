#!/usr/bin/env ocaml

(*******************)
(* Hardcoded files *)
(*******************)

let cmake day = Printf.sprintf
{|add_executable(%s main.cpp)
|} day

let main_cpp _day = Printf.sprintf
{|#include <filesystem>
#include <fstream>
#include <print>
#include <ranges>
#include <string>
#include <string_view>

std::string read_file(const std::filesystem::path& path) {
    std::ifstream in(path);
    if (!in) {
        throw std::runtime_error("Cannot open file: " + path.string());
    }
    std::ostringstream s;
    s << in.rdbuf();
    return s.str();
}

[[nodiscard]] constexpr auto lines(std::string_view sv) {
    // Remove trailing '\n'
    while (!sv.empty() && sv.back() == '\n') sv.remove_suffix(1);
    return sv | std::views::split('\n');
}

long long solve(std::string_view contents) {
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::println("Usage: program <filepath>");
        return 1;
    }

    std::filesystem::path file_path = argv[1];
    auto file_contents = read_file(file_path);

    std::println("{}", solve(file_contents));
}
|}

(***************)
(* Main logic *)
(***************)

let write_file ~path contents =
    Out_channel.with_open_bin path (fun t -> Out_channel.output_string t contents)

let gen day_str =
    let day_num = int_of_string day_str in
    let day = Printf.sprintf "day%02d" day_num in
    if not (Sys.file_exists day) then (
        Sys.mkdir day 0o755;

        let cmake_path = Printf.sprintf "%s/CMakeLists.txt" day in
        write_file ~path:cmake_path (cmake day);

        let main_path = Printf.sprintf "%s/main.cpp" day in
        write_file ~path:main_path (main_cpp day)
    )

(********)
(* Main *)
(********)

let () =
    let argv = Sys.argv in
    if Array.length argv < 2 then
        print_endline "Usage: ./gen_day.ml 5"
    else
        gen argv.(1)

