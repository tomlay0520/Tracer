# it is a script to visualize the caller & callee relationship diagram
# It reads a trace file and generates a call graph using NetworkX and Matplotlib.
# The trace file should contain lines with "ENTER: function_name" and "EXIT: function_name".
# Usage: python test.py (trace file should be named 'trace')
# The output will be saved as 'call_graph.png'.
# written by Lei Tang, 2025-09-02 department of software engineering, Shanghai University of Electric Power
import matplotlib.pyplot as plt
import networkx as nx
from collections import defaultdict

# Parse the trace file to build the call graph
def parse_trace(trace_file):
    call_stack = []
    call_graph = defaultdict(set)

    with open(trace_file, 'r') as f:
        for line in f:
            if line.startswith('ENTER:'):
                func_name = line.strip().split('ENTER: ')[1]
                if call_stack:
                    caller = call_stack[-1]
                    call_graph[caller].add(func_name)
                call_stack.append(func_name)
            elif line.startswith('EXIT:'):
                if call_stack:
                    call_stack.pop()

    return dict(call_graph)

# Visualize the call graph using NetworkX and Matplotlib
def visualize_call_graph(call_graph, output_file):
    G = nx.DiGraph()

    for caller, callees in call_graph.items():
        for callee in callees:
            G.add_edge(caller, callee)

    plt.figure(figsize=(14, 10))

    try:
        pos = nx.nx_agraph.graphviz_layout(G, prog='dot')
    except:
        pos = nx.spring_layout(G, k=2, iterations=50)

    node_colors = []
    for node in G.nodes():
        if node == 'main':
            node_colors.append('lightblue')
        elif G.in_degree(node) == 0:
            node_colors.append('lightgreen')
        else:
            node_colors.append('lightyellow')

    nx.draw_networkx_nodes(G, pos, node_color=node_colors,
                           node_size=2500, alpha=0.8)

    nx.draw_networkx_edges(G, pos, edge_color='gray',
                           arrowstyle='->', arrowsize=20,
                           connectionstyle="arc3,rad=0.1")

    nx.draw_networkx_labels(G, pos, font_size=9,
                            font_weight='bold')

    plt.title('Function-Call Diagram by Lei Tang, Dept of Software Engineering', fontsize=16, fontweight='bold')
    plt.axis('off')
    plt.tight_layout()
    plt.savefig(f'{output_file}.png', dpi=300, bbox_inches='tight')
    plt.show()

    print(f"caller & callee relationship diagram is: {output_file}.png")

call_graph = parse_trace('trace')
visualize_call_graph(call_graph, 'call_graph')