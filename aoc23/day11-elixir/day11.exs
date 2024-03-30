defmodule Aoc2023.Day11 do

  @input_file Path.dirname(__ENV__.file) <> "/input.txt"
  @test_file Path.dirname(__ENV__.file) <> "/test.txt"

  def part1(path) do
    path
    |> parse_input()
    |> build_graph()
    |> identify_expansions()
    |> identify_galaxies()
    |> calc_min_distances(1)
    |> Enum.map(fn dists -> Enum.sum(dists) end)
    |> Enum.sum()
  end

  def part2(path) do
    path
    |> parse_input()
    |> build_graph()
    |> identify_expansions()
    |> identify_galaxies()
    |> calc_min_distances(999999)
    |> Enum.map(fn dists -> Enum.sum(dists) end)
    |> Enum.sum()
  end

  defp parse_input(path) do
    path
    |> Input.to_array()
  end

  defp build_graph(input_array) do
    {
      input_array |> length(),
      input_array |> List.first() |> String.length(),
      input_array
      |> Stream.with_index()
      |> Enum.reduce(%{}, fn {row, x}, acc1 ->
        row
        |> String.split("", trim: true)
        |> Stream.with_index()
        |> Enum.reduce(acc1, fn {char, y}, acc2 ->
          Map.put(acc2, {x, y}, char)
        end)
      end)
    }
  end

  defp identify_expansions({x_length, y_length, galaxy_map}) do
    x_expansion =
      0..(x_length - 1)
      |> Enum.reduce([], fn x, acc ->
        row_coors = 0..(y_length - 1) |> Enum.map(fn y -> {x, y} end)
        if Enum.all?(row_coors, fn coor -> Map.get(galaxy_map, coor) == "." end) do
          [x | acc]
        else
          acc
        end
      end)

    y_expansion =
      0..(y_length - 1)
      |> Enum.reduce([], fn y, acc ->
        row_coors = 0..(x_length - 1) |> Enum.map(fn x -> {x, y} end)
        if Enum.all?(row_coors, fn coor -> Map.get(galaxy_map, coor) == "." end) do
          [y | acc]
        else
          acc
        end
      end)

    {x_expansion, y_expansion, galaxy_map}
  end

  defp identify_galaxies({x_exp, y_exp, galaxy_map}) do
    galaxy_pos =
      galaxy_map
        |> Map.to_list()
        |> Enum.reduce([], &identify_galaxies/2)

    {galaxy_pos, x_exp, y_exp}
  end
  defp identify_galaxies({pos, char}, acc) do
    if Regex.match?(~r/\d|#/, char) do
      [pos | acc]
    else
      acc
    end
  end

  defp calc_min_distances(galaxy_data, expansion) when is_integer(expansion), do: calc_min_distances(galaxy_data, expansion, [])
  defp calc_min_distances({[], _x_expansions, _y_expansions}, _expansion, min_dists), do: min_dists
  defp calc_min_distances({[pos | tail], x_expansions, y_expansions}, expansion, min_dists) do
    dists = tail |> Enum.map(fn pos2 -> min_distance(pos, pos2, {x_expansions, y_expansions, expansion}) end)
    calc_min_distances({tail, x_expansions, y_expansions}, expansion, [dists | min_dists])
  end

  defp min_distance({x1, y1}, {x2, y2}, {x_expansion, y_expansion, expansion}) do
    {min_x, max_x} = [x1, x2] |> Enum.sort() |> List.to_tuple()
    {min_y, max_y} = [y1, y2] |> Enum.sort() |> List.to_tuple()
    x_offset = Enum.count(Enum.filter(x_expansion, fn xe -> min_x < xe && xe < max_x  end)) * expansion
    y_offset = Enum.count(Enum.filter(y_expansion, fn ye -> min_y < ye && ye < max_y end)) * expansion

    abs(x2 - x1) + abs(y2 - y1) + x_offset + y_offset
  end
end


Aoc2023.Day11.part2("input.txt") |> IO.inspect()
