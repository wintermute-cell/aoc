defmodule Day6 do
  defp calc_race_options({record_time, distance}) do
    Stream.iterate(1, &(&1 + 1))
      |> Stream.map(fn hold_time -> (record_time - hold_time) * hold_time end)
      |> Stream.drop_while(&(&1 <= distance)) 
      |> Stream.take_while(&(&1 > distance)) 
      |> Enum.count()
  end

  def calc_race_options_quad_eq({record_time, distance}) do
    a = -1
    b = record_time
    c = -distance
    delta = b * b - 4 * a * c
    cond do
      delta < 0 ->
        0
      true -> 
        root1 = (-b - :math.sqrt(delta)) / (2 * a)
        root2 = (-b + :math.sqrt(delta)) / (2 * a)
        min_hold_time = max(1, :math.ceil(root1))
        max_hold_time = min(record_time, :math.floor(root2))
        -max_hold_time + min_hold_time - 1
    end
  end

  def part1(path) do
    {:ok, content} = File.read(path)
    content
      |> String.split("\n", trim: true)
      |> Enum.map(fn line ->
        line |> String.split |> Enum.drop(1) |> Enum.map(&String.to_integer/1)
      end)
      |> Enum.zip
      |> Enum.map(&(Task.async(fn -> calculate_winning_options(&1) end)))
      |> Enum.map(&Task.await/1)
      |> Enum.product()
  end

  def part2(path) do
    {:ok, content} = File.read(path)
    content
      |> String.split("\n", trim: true)
      |> Enum.map(fn line ->
        line |> String.replace(" ", "") |> String.split(":") |> Enum.drop(1) |> Enum.map(&String.to_integer/1)
      end) 
      |> Enum.zip
      #|> Enum.map(&(Task.async(fn -> calc_race_options_quad_eq(&1) end)))
      |> Enum.map(&(Task.async(fn -> calc_race_options(&1) end)))
      |> Enum.map(&Task.await/1)
      |> Enum.product()
  end
end

Day6.part2("input.txt") |> IO.inspect(charlists: :as_lists)
