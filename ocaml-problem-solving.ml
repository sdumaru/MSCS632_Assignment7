(* Calculate the mean of a list of ints *)
let calculate_mean lst =
  let sum = List.fold_left (+) 0 lst in
  float_of_int sum /. float_of_int (List.length lst)

(* Calculate the median of a list of ints *)
let calculate_median lst =
  let sorted = List.sort compare lst in
  let len = List.length sorted in
  if len mod 2 = 1 then
    float_of_int (List.nth sorted (len / 2))
  else
    let a = List.nth sorted (len / 2 - 1) in
    let b = List.nth sorted (len / 2) in
    (float_of_int (a + b)) /. 2.0

(* Calculate the mode(s) of a list of ints *)
let calculate_mode lst =
  (* build a frequency map *)
  let freq_map =
    List.fold_left 
    (fun acc x ->
      let count = try List.assoc x acc with Not_found -> 0 in
      (x, count + 1) :: List.remove_assoc x acc
    ) [] lst
  in
  (* find max frequency *)
  let max_count =
    List.fold_left (fun m (_,cnt) -> if cnt > m then cnt else m) 0 freq_map
  in
  (* collect all values with that frequency *)
  List.filter (fun (_, cnt) -> cnt = max_count) freq_map
  |> List.map fst, max_count

let () =
  let test_data = [1; 2; 3; 4; 5] in
  let m = calculate_mean test_data in
  let med = calculate_median test_data in
  let modes, freq = calculate_mode test_data in
  Printf.printf "Data: [%s]\n"
    (String.concat "; " (List.map string_of_int test_data));
  Printf.printf "Mean:   %.2f\n" m;
  Printf.printf "Median: %.2f\n" med;
  Printf.printf "Mode (%d occurrence%s): [%s]\n"
    freq (if freq>1 then "s" else "")
    (String.concat "; " (List.map string_of_int modes))
