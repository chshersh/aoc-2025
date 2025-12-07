#!/usr/bin/env ocaml

(*******************)
(* Hardcoded files *)
(*******************)

let cmake day = Printf.sprintf
{|add_day(%s main.cpp)
|} day

let main_cpp = Printf.sprintf
{|// std includes
#include <string_view>

// local
#include <aoc_common.hpp>

long long solve(std::string_view contents) {
    return 0;
}

int main(int argc, char* argv[]) {
    auto file_contents = aoc::read_input_file(argc, argv);
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
        write_file ~path:main_path main_cpp
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

