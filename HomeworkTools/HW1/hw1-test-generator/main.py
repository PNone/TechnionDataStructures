import random

# Generate the first set of 50 random positive integers
horse_ids = [random.randint(1, 50) for _ in range(50)]

speeds = [random.randint(1, 50) for _ in range(50)]

# Generate the second set of 50 random positive integers
herd_ids = [random.randint(2000, 2003) for _ in range(50)]

ops = [
    "add_herd","remove_herd","add_horse","join_herd",
    "follow","leave_herd","get_speed","leads","can_run_together"
]

for test in range(41, 100):
    with open(f'generated/test{test}.in', 'w') as f:
        for cmd_id in range(1, 60_000):
            command = random.choice(ops)
            horse1 = random.choice(horse_ids)
            horse2 = random.choice(horse_ids)
            herd = random.choice(herd_ids)
            if command == "add_herd":
                f.write(f'{command} {herd}\n')
            elif command == "remove_herd":
                f.write(f'{command} {herd}\n')
            elif command == "add_horse":
                speed = random.choice(speeds)
                f.write(f'{command} {horse1} {speed}\n')
            elif command == "join_herd":
                join_both = random.choice([True, False])
                f.write(f'{command} {horse1} {herd}\n')
                if join_both:
                    f.write(f'{command} {horse2} {herd}\n')
            elif command == "follow":
                f.write(f'{command} {horse1} {horse2}\n')
            elif command == "leave_herd":
                join_both = random.choice([True, False])
                f.write(f'{command} {horse1}\n')
                if join_both:
                    f.write(f'{command} {horse2}\n')
            elif command == "get_speed":
                f.write(f'{command} {horse1}\n')
            elif command == "leads":
                f.write(f'{command} {horse1} {horse2}\n')
            elif command == "can_run_together":
                f.write(f'{command} {herd}\n')
