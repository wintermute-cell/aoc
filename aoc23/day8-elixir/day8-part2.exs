defmodule Parallel do
  def pmap(collection, func) do
    collection
    |> Enum.map(&(Task.async(fn -> func.(&1) end)))
    |> Enum.map(&Task.await/1)
  end
end

defmodule PatternOverlap do
  def lcm(a, b), do: div(a * b, gcd(a, b))
  
  def gcd(a, 0), do: a
  def gcd(a, b), do: gcd(b, rem(a, b))

  def find_overlap(intervals) do
    Enum.reduce(intervals, 1, &lcm/2)
  end
end

defmodule Graph do
  @spec create_graph() :: map
  def create_graph do
    %{}
  end

  @spec add_node(map, String.t) :: map
  def add_node(graph, node_name) do
    case Map.has_key?(graph, node_name) do
        false -> Map.put_new(graph, node_name, %{l: nil, r: nil})
        _ ->     graph
    end
  end

  @spec add_node_with_neighbors(map, String.t, String.t, String.t) :: map
  def add_node_with_neighbors(graph, node_name, l, r) do
    graph = add_node(graph, node_name)
    graph = add_node(graph, l)
    graph = add_node(graph, r)
    graph = add_edge(graph, :left, node_name, l)
    graph = add_edge(graph, :right, node_name, r)
    graph
  end

  @spec add_edge(map, :atom, String.t, String.t) :: map
  def add_edge(graph, side, from, to) do
    case side do
      :left -> 
        graph |> Map.update(from, %{l: to, r: nil}, fn %{l: _, r: currr} -> %{l: to, r: currr} end)
      :right -> 
        graph |> Map.update(from, %{l: nil, r: to}, fn %{l: currl, r: _} -> %{l: currl, r: to} end)
    end
  end

  @spec get_neighbor(map, atom, String.t) :: map
  def get_neighbor(graph, side, node) do
    case side do
      :left ->
        Map.get(graph, node, %{l: nil, r: nil}).l
      :right ->
        Map.get(graph, node, %{l: nil, r: nil}).r
    end
  end
end

defmodule Day8 do
  def solve(input) do
    [path | nodes] = input |> String.split("\n", trim: true)
    path_list = path |> String.graphemes

    # strings to graph
    graph = nodes |> Enum.reduce(Graph.create_graph, fn node_string, graph ->
      [node, lneighbor, rneighbor] = tl(Regex.run(~r/([A-Z\d]{3}) = \(([A-Z\d]{3}), ([A-Z\d]{3})\)/, node_string))
      graph |> Graph.add_node_with_neighbors(node, lneighbor, rneighbor)
    end)

    # all nodes that start with A
    starts = nodes |> Enum.map(fn line ->
      line |> String.split |> hd
    end) |> Enum.filter(fn name -> name |> String.ends_with?("A") end)

    starts 
    |> Parallel.pmap(fn start_node -> ghost_walk(start_node, path_list, graph) |> elem(1) end)
    |> PatternOverlap.find_overlap()
  end

  defp ghost_walk(start_node, path_list, graph) do
    path_list |> Stream.cycle |> Enum.reduce_while({start_node, 0}, fn step_direction, {curr_node, step_count} -> 
      case step_direction do
        "R" ->
          next_node = Graph.get_neighbor(graph, :right, curr_node)
          checkZZZ(next_node, step_count)
        "L" ->
          next_node = Graph.get_neighbor(graph, :left, curr_node)
          checkZZZ(next_node, step_count)
      end
    end)
  end

  defp checkZZZ(node, step_count) do
    cond do
      node |> String.ends_with?("Z") ->
        {:halt, {node, step_count+1}}
      true ->
        {:cont, {node, step_count+1}}
    end
  end

  def read_file(path) do
    {:ok, contents} = File.read(path)
    contents
  end
  
end

Day8.read_file("input.txt") |> Day8.solve |> IO.inspect(charlists: :as_lists)
