from itertools import combinations

def count_slots(s):
    """
    Count the number of slots (sequences of '?' or '#') in the string.
    """
    slots = []
    in_slot = False
    start = 0

    for i, char in enumerate(s):
        if char in '?#' and not in_slot:
            in_slot = True
            start = i
        elif char not in '?#' and in_slot:
            slots.append((start, i - 1))
            in_slot = False

    if in_slot:
        slots.append((start, len(s) - 1))

    return slots

def count_arrangements(s, groups):
    slots = count_slots(s)
    total_ways = 0

    for slot_indices in combinations(range(len(slots)), len(groups)):
        ways = 1
        for group, slot_index in zip(groups, slot_indices):
            slot = slots[slot_index]
            slot_length = slot[1] - slot[0] + 1
            if group <= slot_length:
                # Number of ways to place the group in the slot
                ways *= (slot_length - group + 1)
            else:
                ways = 0
                break
        total_ways += ways

    return total_ways

# Test cases
test_cases = [
    ("???.###", [1, 1, 3]),
    (".??..??...?##.", [1, 1, 3]),
    ("?#?#?#?#?#?#?#?", [1, 3, 1, 6]),
    ("????.#...#...", [4, 1, 1]),
    ("????.######..#####.", [1, 6, 5]),
    ("?###????????", [3, 2, 1])
]

for test in test_cases:
    print(f"{test[0]} {test[1]} -> {count_arrangements(*test)} arrangements")

