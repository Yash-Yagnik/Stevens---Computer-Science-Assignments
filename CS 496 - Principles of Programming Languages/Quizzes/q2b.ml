(* 
     Quiz 2 - 7 Feb 2024
     Name1: Yash Yagnik
     Name2: Eduardo Hernandez
 *)


 type 'a bt = Empty |  Node of 'a*'a bt*'a bt

 (* Helper function that builds a leaf *)
 let leaf n = Node(n,Empty,Empty)
 
 (* Two sample binary trees.
    The first one is a BST, but not the second one *)
 let t1 : int bt = Node(12,
                        Node(7,Empty,leaf 10),
                        Node(24,
                             leaf 14,
                             Empty))
 
 let t2 : int bt = Node(12,
                        leaf 7,
                        Node(24,
                             leaf 30,
                             Empty))
 
 (** returns smallest element in non-empty tree [t].
     Fails if [t] is empty, it should fail. 
     Note: the tree [t] is not assumed to be a bst *)
let rec mint : 'a bt -> 'a =
  fun t ->
    match t with 
  | Empty -> failwith "Tree is empty"
  | Node (root, left, right) ->
    let left_min = mint left in
    let right_min = mint right in
    if root <= left_min && root <= right_min then
      root
    else if left_min <= right_min then
      left_min
    else
      right_min


 (** returns largest element in non-empty tree [t].
     Fails if [t] is empty, it should fail. 
     Note: the tree [t] is not assumed to be a bst *)
 let rec maxt : 'a bt -> 'a =
     fun t ->
      match t with
     | Empty -> failwith "Tree is empty"
     | Node (root, left, right) ->
       let left_max = mint left in
       let right_max = mint right in
       if root >= left_max && root >= right_max then
        root
       else if left_max >= right_max then
         left_max
       else
         right_max
   
 
 (** [is_bst t] determines whether the binary tree [t] is a binary search tree *)
 let rec is_bst : 'a bt -> bool =
   fun t ->
     let rec helper t min_value max_value =
       match t with
       | Empty -> true
       | Node (value, left, right) ->
       value > min_value && value < max_value && helper left min_value value && helper right value max_value in
       helper t min_int max_int

let rec add : 'a -> 'a bt -> 'a bt =
fun k t ->
  match t with
  | Empty -> Node (k, Empty, Empty)
  | Node (value, left, right) ->
    if k < value then
      Node (value, add k left, right)
    else if k > value then
      Node (value, left, add k right)
    else
      failwith "Key is in the tree"