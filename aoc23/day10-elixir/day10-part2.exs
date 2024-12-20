defmodule GameMap do
  def create_map(input) do
    lines = input |> String.split("\n", trim: true)
    chars = lines |> Enum.map(&String.graphemes/1)
    wd = length(hd(lines) |> String.graphemes)
    %{content: chars |> List.flatten, lines: chars, width: wd, height: length(chars |> List.flatten)/wd}
  end

  def get_at(map, {x, y}) do
    idx = pos_to_idx(map, {x, y})
    cond do
      x < map.width && y < map.height -> {:ok, map.content |> Enum.at(idx)}
      true -> {:out_of_bounds, ""}
    end
  end

  def idx_to_pos(map, idx) do
    x = rem(idx, map.width)
    y = div(idx, map.width)
    {x, y}
  end

  def pos_to_idx(map, {x, y}) do
    y*map.width + x
  end
end

defmodule Day10Part2 do
  def read_file(path) do
    {:ok, content} = File.read(path)
    content
  end

  def solve(input) do
    path = read_file("path.txt") 
      |> String.split("\n", trim: true) 
      |> Enum.map(fn line -> 
        line |> String.split(", ") |> Enum.map(&String.to_integer/1)
      end)

    game_map = GameMap.create_map(input)

    game_map.lines |> Enum.with_index() |> Enum.reduce(0, fn {line, line_idx}, acc ->
      inside_this_line = line |> Enum.with_index() |> Enum.reduce({0, false}, fn {char, char_idx}, {curr_inside, is_inside} ->
        cond do
          Enum.member?(["|", "L", "J", "F", "7", "-"], char) && Enum.member?(path, [char_idx, line_idx]) ->
            {curr_inside, !is_inside}
          !Enum.member?(path, [char_idx, line_idx]) && is_inside -> 
            {curr_inside+1, is_inside}
          true ->
            {curr_inside, is_inside}
        end
      end)
      {line, inside_this_line}
      (inside_this_line |> elem(0)) + acc
    end)

  end
end

Day10Part2.read_file("input.txt") |> Day10Part2.solve |> IO.inspect(charlists: :as_lists)
