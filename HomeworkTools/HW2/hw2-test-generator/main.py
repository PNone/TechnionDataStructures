import random

# Generate the first set of 50 random positive integers
jockey_ids = [random.randint(1, 900) for _ in range(400)]


# Generate the second set of 50 random positive integers
team_ids = [random.randint(2000, 10_000) for _ in range(200)]

ops = [
    "add_team","add_jockey","update_match","merge_teams",
    "unite_by_record", "get_jockey_record","get_team_record"
]

for test in range(41, 100):
    with open(f'generated/test{test}.in', 'w') as f:
        for cmd_id in range(1, 60_000):
            command = random.choice(ops)
            jockey1 = random.choice(jockey_ids)
            jockey2 = random.choice(jockey_ids)
            team1 = random.choice(team_ids)
            team2 = random.choice(team_ids)
            if command == "add_team":
                f.write(f'{command} {team1}\n')
            elif command == "add_jockey":
                f.write(f'{command} {team1}\n')
            elif command == "update_match":
                f.write(f'{command} {jockey1} {jockey2}\n')
            elif command == "merge_teams":
                f.write(f'{command} {team1} {team2}\n')
            elif command == "unite_by_record":
                record = random.randint(-100, 100)
                f.write(f'{command} {record}\n')
            elif command == "get_jockey_record":
                f.write(f'{command} {jockey1}\n')
            elif command == "get_team_record":
                f.write(f'{command} {team1}\n')
