defmodule FileHandler do
  def write_tuples_to_file(tuples, file_path) do
    # Convert the list of tuples to a string
    content = Enum.map(tuples, &inspect/1) |> Enum.join(",\n   ")

    # Add brackets and newlines to match the desired format
    formatted_content = "[\n   " <> content <> "\n]"

    # Write the formatted content to the file
    case File.write(file_path, formatted_content) do
      :ok -> :ok
      {:error, reason} -> {:error, reason}
    end
  end
end

defmodule GameMap do
  def create_map(input) do
    lines = input |> String.split("\n", trim: true)
    chars = lines |> Enum.map(&String.graphemes/1)
    wd = length(hd(lines) |> String.graphemes)
    %{content: chars |> List.flatten, width: wd, height: length(chars |> List.flatten)/wd}
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

defmodule Day10 do
  def read_file(path) do
    {:ok, content} = File.read(path)
    content
  end

  def solve(input) do
    game_map = input |> GameMap.create_map()
    start_idx = game_map.content |> Enum.reduce_while(0, fn char, acc ->
      case char do
        "S" -> {:halt, acc}
        _ -> {:cont, acc + 1}
      end
    end)
    GameMap.idx_to_pos(game_map, start_idx) |> IO.inspect()
    {distance, path, _} = walk_pipe(game_map, GameMap.idx_to_pos(game_map, start_idx), {0, 0}, true)
    FileHandler.write_tuples_to_file(path, "path.")
    #distance / 2
  end

  defp walk_pipe(game_map, {curr_x, curr_y}, came_from, first_step) do
    {_, curr_char} = GameMap.get_at(game_map, {curr_x, curr_y})
    case curr_char do
      "S" when first_step |> Kernel.not -> {0, [], false}
      _ ->
        possible_directions = [{1, 0}, {-1, 0}, {0, 1}, {0, -1}]
          |> Enum.filter(fn {dir_x, dir_y} -> {-dir_x, -dir_y} != came_from end)
          |> Enum.filter(fn {dir_x, dir_y} ->
            {ok, next_char} = GameMap.get_at(game_map, {dir_x+curr_x, dir_y+curr_y})
            case ok do
              :ok -> true
              _ ->   false
            end
          end)
          |> Enum.filter(fn dir ->
            cond do
              (dir == {1, 0} || dir == {-1, 0}   ) && curr_char == "-" -> true
              (dir == {0, 1} || dir == {0, -1}   ) && curr_char == "|" -> true
              (dir == {0, -1} || dir == {1, 0}  ) && curr_char == "L" -> true
              (dir == {0, -1} || dir == {-1, 0} ) && curr_char == "J" -> true
              (dir == {0, 1} || dir == {-1, 0}  ) && curr_char == "7" -> true
              (dir == {0, 1} || dir == {1, 0}   ) && curr_char == "F" -> true
              curr_char == "S" -> true
              true -> false
            end
          end)
          |> Enum.filter(fn {dir_x, dir_y} ->
            {ok, next_char} = GameMap.get_at(game_map, {dir_x+curr_x, dir_y+curr_y})
            ~w(| - L J 7 F . S) |> Enum.member?(next_char)
          end)
          |> Enum.filter(fn {dir_x, dir_y} ->
            {ok, next_char} = GameMap.get_at(game_map, {dir_x+curr_x, dir_y+curr_y})
            cond do
              curr_char == "S" && ~w(|) |> Enum.member?(next_char) -> false
               true -> true 
            end
          end)
        next_positions = possible_directions
          |> Enum.map(fn {dir_x, dir_y} ->
            {dist, path, deadend} = walk_pipe(game_map, {curr_x+dir_x, curr_y+dir_y}, {dir_x, dir_y}, false)
            {dist+1, [{curr_x, curr_y} | path], deadend} 
          end)
          |> Enum.filter(fn {dist, path, deadend} ->
            !deadend
          end)

        cond do
          length(next_positions) == 0 -> {-1, [], true}
            true -> 
              next_positions |> Enum.min_by(fn {dist, _, _} ->
              dist
            end)
        end
    end
  end
end

Day10.read_file("input.txt") |> Day10.solve |> IO.inspect(charlists: :as_lists)
