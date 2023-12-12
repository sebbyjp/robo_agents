Application calls
    env.get_obs
    agent.act(obs)

Ros app calls:
    agent_server.get_action() = observer.get_obs(), return agent.act()
    

Agent:
    observer
    supervisor
    stateEstimator
    Agent(Observer, Supervisor, policy, StateEstimator)
    state(obs[])
    {
        return StateEstimator.estimate(obs[])
    }
  act(state) {
        policy(state)
    }
    act(obs) {
        observer.cache_insert(obs)
        net(state(obs.get(0, N)))
    }

    update(reward) {
        supervisor.cache_insert(reward)
        policy.update(supervisor.get(0, EpisodeLength))
    }


<ObsT, SrcT>
observer:
    cache
    srcs

    Observer(ObsFromSrcsFunc)
    observe_new()
    getLast(N)
    get(id, last)
    cache_insert(obs)


supervisor:
    cache
    supervise(obs) -> rew
    getLast()
    get()
    cache_insert()

datasetwriter:
    DataGenerator( episode_length, folder_out, folder_out_format=hd5);
    record(a, r, obs, prev_obs)

<ObsT, SrcT>
RosObserver : class Observer
    RosObserver(node)

RosAgent aka  actor aka PolicyServer:
    Agent agent;
    DatasetWriter? dg;
    AgentServer() {
        observer = observer();
        agent = Agent()

    }
    bool action_callback() {
        obs = agent.observer.observe_new()
        return agent.act(obs)
    }
    bool supervise_callback(record_task?, ) {
        obs = agent.observer.observe_new()
        r agent.supervisor.supervise(obs)

    }
    update_callback(r){
        agent.update(r)
    }

    virtual act() = 0;
    virtual observe() = 0;
    virtual estimate_state(obs[]) {return obs[0]}





EnvRos:
    Agent
    Moveit task;
    reset();
    obs(){ return agent.observer_.observe_new(cache=false)}
    step(act) { 
         task.execute(act)
         obs = agent.observer_.observe(cache=false)
        r = agent.supervisor.suervise(obs)
        return obs, r
        }

script:
    loop:
        act = agent.act()
        r = env.step(act)

