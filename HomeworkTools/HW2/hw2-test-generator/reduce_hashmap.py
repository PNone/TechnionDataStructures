with open(f'generated/test100.in', 'w') as f:
    for team_id in range(1, 20_000):
        f.write(f'add_team {team_id}\n')
    for team_id in range(2, 20_000):
        f.write(f'merge_teams 1 {team_id}\n')