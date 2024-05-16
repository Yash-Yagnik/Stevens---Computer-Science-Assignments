(* Quiz 1 - 31 January 2024

   Student name 1: Yash Yagnik
   Student name 2: Eduardo Hernandez
   "I pledge my honor that I have abided by the Stevens Honor System."
*)


(* Notes: 
    a. You may add helper functions.
    b. "let rec" allows your function to be recursive, but it doesn't
    have to be. 
*)

(* Sample Tree *)
let ex = [(12, 7); (12, 43); (7, 4); (43, 33); (43,77)]

(*
      12
      /\ 
     /  \  
    7   43
   /    /\ 
  /    /  \  
 4    33  77
*)

(** [sub l1 l2] returns the list resulting from subtracting every 
    element in [l2] from [l1].
    Eg. sub [1;2] [] => [1; 2]
    Eg. sub [1;2;1] [1] => [2]
    Eg. sub [1;2] [2;3;1] => []
*)
let rec sub l1 l2 =
  match l2 with
  | [] -> l1
  | hd :: tl ->
    if List.mem hd l1 then
      sub (List.filter (fun x -> x <> hd) l1) tl
    else
      sub l1 tl
    
(** [outgoing_nodes t n] returns the list of nodes outgoing from node
 ** [n] in the tree [t]. You may assume the node [n] exists in the
 ** tree [t] .
 ** Eg. outgoing_nodes ex 12 => [7; 43]
*)
let rec outgoing_nodes t (n:int) =
  match t with 
  | [] -> []
  | (root, child) :: list_tail -> 
    if root = n then 
      child :: outgoing_nodes list_tail (n:int)
  else outgoing_nodes list_tail (n:int)
    
(**  [nodes t] returns the list of nodes of the tree without
    duplicates. The order of the
   nodes in the list is irrelevant.
   eg. nodes ex => [12; 7; 4; 33; 43; 77]*)

let rec nodes t =
  failwith "complete"
    
(** [leaves t] returns the leaves of the tree [t]
   Eg. leaves ex =>  [4; 33; 77]
*)
(*let rec leaves t =
  match t with
  | [] -> []
  | (leaf, Empty, Empty) -> leaf :: leaves lt :: leaves rt
  | (node, lt, rt) -> leaves lt :: leaves rt (* you can also add when clauses when lt <> Empty*)*)


(* 
   Returns the root of a tree
   Eg. root ex =>  [12]
*)
let rec root t =
  let all_nodes = List.concat_map (fun (parent, child) -> [parent; child]) t in
  let all_parents = List.map fst t in
  let root_candidate = List.find (fun node -> not (List.mem node all_parents)) all_nodes in
  [root_candidate]

(* 
   Returns the boolean indicating if the tree is a binary tree.
   Eg. is_binary ex =>  true
*)
let rec is_binary t =
  failwith "complete"

(** [subtree t n] returns the subtree rooted at node [n]. (extra-credit)
 **  Eg. subtree ex 12 => [(43, 33); (43, 77); (7, 4); (12, 7); (12, 43)]
         subtree ex 43 -=> [(43, 33); (43, 77)]
         subtree ex 7 => [(7, 4)]
         subtree ex 4 => []
*)
let rec subtree t (n:int) =
  match t with 
  | [] -> []
  | (root, tail) -> root
                               

