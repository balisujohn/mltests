from matplotlib import pyplot as plt
import numpy as np
import sys
import json

def generate_agent_histograms(save_data):
    agents = save_data['agents']
    ages = [agents[key]['age'] for key in agents]
    mutations = [agents[key]['mutations'] for key in agents]
    plt.figure(1)
    plt.hist(ages, bins='auto')
    plt.figure(2)
    plt.hist(mutations, bins='auto')
    plt.show()


if __name__ == "__main__":
    with open(sys.argv[1]) as json_file:
        save = json.load(json_file)
        generate_agent_histograms(save)