import matplotlib.pyplot as plt


def parse_throughput(filename, interval=0.1):
    times = []
    throughputs = []
    current_window = 0
    bytes_in_window = 0

    with open(filename, 'r') as f:
        for line in f:
            t, bits = line.strip().split()
            t = float(t)
            bits = float(bits)

            if t > current_window + interval:
                # Store Data for previous window
                times.append(current_window)
                # Convert bits to Mbps
                throughputs.append((bytes_in_window) / (interval * 1e6))

                # Advance window
                current_window += interval
                bytes_in_window = 0

            bytes_in_window += bits
    return times, throughputs


def parse_queue(filename):
    times = []
    sizes = []
    with open(filename, 'r') as f:
        for line in f:
            t, size = line.strip().split()
            times.append(float(t))
            sizes.append(int(size))
    return times, sizes


# --- Plot 1: Throughput ---
t_udp, th_udp = parse_throughput("udp_throughput.dat")
t_tcp, th_tcp = parse_throughput("tcp_throughput.dat")

plt.figure(figsize=(10, 5))
plt.plot(t_udp, th_udp, 'r-', label='UDP Flow (n0)')
plt.plot(t_tcp, th_tcp, 'b-', label='TCP Flow (n1)')
plt.xlabel('Time (s)')
plt.ylabel('Throughput (Mbps)')
plt.title('Task 2: TCP vs UDP Throughput Competition')
plt.legend()
plt.grid(True)
plt.savefig("throughput_graph.png")
print("Generated throughput_graph.png")

# --- Plot 2: Queue Occupancy ---
t_q, size_q = parse_queue("queue_occupancy.dat")

plt.figure(figsize=(10, 5))
plt.plot(t_q, size_q, 'k-')
plt.xlabel('Time (s)')
plt.ylabel('Queue Size (Packets)')
plt.title('Queue Occupancy at Node 2 (Bottleneck)')
plt.grid(True)
plt.savefig("queue_graph.png")
print("Generated queue_graph.png")
