from matplotlib import pyplot as plt
import numpy as np
import sys
import json
sys.path.insert(0,"./base_SNN")
import brain


def generate_agent_histograms(save_data):
    agents = save_data['agents']
    ages = [agents[key]['age'] for key in agents]
    mutations = [agents[key]['mutations'] for key in agents]
    plt.figure(1)
    plt.hist(ages, bins='auto')
    plt.figure(2)
    plt.hist(mutations, bins='auto')
    plt.show()


def extract_longest_lived_brain(save_data):
    agents = save_data['agents']
    key = max(agents, key=lambda key: agents[key]['age'] )
    print(agents[key]['age'])
    return brain.load_brain_from_json(agents[key]['brain'])




if __name__ == "__main__":
    with open(sys.argv[1]) as json_file:
        save = json.load(json_file)
        #generate_agent_histograms(save)
        best_brain = extract_longest_lived_brain(save)
        print(brain.print_brain_to_json(best_brain))