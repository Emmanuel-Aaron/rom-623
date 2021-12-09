Introduction to the ROM-623
	
The ROM-623 is a semi autonomous aerocraft, specifically an aeroplane that was developed over the course of 3 months for the purpose of conducting research in hard real-time embedded system applications. The ROM-623's central component is a dynamic hard real-time scheduler on a AVR based microcontroller. During the research application factors such as constraints, limitations, and potential applications of the system were recorded for documentation and post analysis for future revisions or similar applications.
The aeroplane consists of hard and soft ware systems which are analyzed separately utilizing a breakdown analysis in the below sections.

The source code for the ROM-623 is available at: https://github.com/Emmanuel-Aaron/rom-623

Figure 1 (ROM-623 staged for test flight)


Hardware Breakdown

Concept Designs
	This subsection reviews the development of the aircrafts’: form factor, electronics, powertrain, and mechanisms for movement. The final prototype was the ROM-623; chosen because of flying regulations that would limit field testing & available material resources. 

Corsair
The Corsair F4U was the first aircraft form investigated for this project, due to this plane’s strong role in world war two combat. The production model of this aeroplane had a wingspan of 12.496m and a working weight of 14,670lbs. The F4U had a length of 10.261m and a height of 4.902m. In early development these dimensions were important for correctly scaling the aircrafts geometry and mass. Since the desirable wingspan was 0.8m, the height and length scaled to 0.3138m & 0.6569m respectively. Scaling the weight by the same ratio was not feasible, because powertrains small enough to fit the geometric scale do not produce enough power (ie. Watts/kg was not feasible at desired scale). Therefore in order to achieve a maximum prototype weight existing models of the Corsair were examined [1-4]. This yielded a practical weight range of 420g-16800g depending on relative wingspan of 0.75m-2.4m. Using this data and incorporating the mass of processor/sensor electronics linear interpolation yielded a reasonable mass of 1600g. The Corsair F4U prototype would have utilized a 6000mAh lithium polymer battery [5] for a 2750W brushless motor, [6] through a 100A ESC [7]. Under this powertrain the Corsair F4U would have been able to maintain a theoretical flight time of 15 minutes, and advanced acrobatic maneuvers. 
The development of this prototype was halted for a number of reasons. In light of expert consultation, with respect to the regulations surrounding drone flight; it became impossible to satisfy the regulatory requirements (licensing etc.) within the short project timeline. Additionally, after a number of different construction materials were investigated it was evident that the project would either go over budget, or body construction would require a massive time investment (limiting time commitments to important elements); neither sacrifice was deemed acceptable so a project overhaul took place.   

Figure 2 (Corsair F4U)


ROM-623
The ROM-623 was the result of a development shift with the intention of producing a sub 250 gram aircraft. The airframe of the ROM-623 was sourced from a novel designer [8]. Some modifications were made from the original design to aid the project's flight goals, such as: landing gear, aerodynamic nose, and weight reduction. The dimensions of the ROM-623 can be found in detail in figure X below, however what is not clear is explained in this section. The ultrasonic sensor is mounted beneath the motor mount, while the ESC, arduino, and all other sensors are inside the nose of the cockpit. The aileron servos were placed inline with the rear triangular stabilizers so that the turbulent air that forms is split and forced into the semi-laminar air over the wings. The elevator servo was placed in the center of the tail to avoid unnecessary imbalancing. The cut slits at the end of each wing are for reducing the area that external forces such as wind are exposed to the aircraft. The reduced area reduces the weight of the aircraft and allows the aircraft to maintain a more stable flight without much loss in  lift. The ROM-623 is propelled by a 115W brushless motor [9], which receives power through the 20A ESC [10], and by a 500mAh battery [11]. The theoretical flight time is 4 minutes which is not inline with the initial design goal. Additionally, the mass of the prototype was 351 grams. The curved leading edge of the wing is also invisible to the eye in the figure below, however it is important to mention because it creates a more efficient airfoil, so generating lift becomes easier. In this design a rudder was not incorporated because it would only increase the weight, giving up yaw control was not a significant sacrifice because the ROM-623 is not meant to perform advanced maneuvers. The airframe is also constructed out of foam board because it is readily available & inexpensive; Ethylene-vinyl acetate was used as the material adhesive, as opposed to Cyanoacrylate which is more expensive. Since Ethylene-vinyl acetate is a weaker bonding agent more was required. A piece of thin acrylic was used for the cockpit cover to restrict the movement of electronics during flight. 

















Figure 3 (ROM-623 Blueprints)


Detailed Analysis

Mechanical
The ROM-623 is able to perform aerial maneuvers through servo actuation on the ailerons and elevator. These 9g servos are powered through the universal battery eliminator circuit on the ESC, and receive their signal from the arduino. The edges of the ailerons were chamifered to mitigate crash impacts by distributing the impact force across a larger area. This chamifer is very important because the ailerons are only connected to the wing by a paper thin sheet. A similar chamifer is visible in figure X above on the elevator. The propeller of the motor is seated midway to the rear of the aeroplane directly behind the cockpit, this forces faster flowing air directly into the elevator allowing for sensitive altitude control. The stacked foam board on the leading ⅓ of the wing exists to generate similar effects to that of a Clark Y airfoil. This provides the aircraft with a better drag to lift ratio, while maintaining soft stall features [11]. In figure X above within the top view, the elevator stabilizers are visible (Right angle triangles connected to the airframe directly behind the propeller), these stabilizers exist to increase the frame's strength against roll forces. Below in figure X is the physical prototype.


Figure 4 (Fully Constructed ROM-623)


Electronic
The electrical systems in the ROM-623 as mentioned before are powered by a 500mAh lithium polymer battery. Under maximum load the motor will draw 7.4A of current to produce 55W of power. Under maximum draw the battery will be completely empty after exactly 4.05 minutes. Once The embedded system power demands are added to the current draw the theoretical flight time can be as low as 2 minutes. A 20A ESC was selected because the motor used is capable of 115W and in the event of a current surge the ESC would need to handle 15.54A. Additionally a buffer was needed because while the rated voltage of the battery is 7.4V, the actual maximum voltage is 8.6V. A complete circuit diagram can be found in figure X below, where the UBEC provides power to the arduino/sensors and the data from the sensors feeds into the arduino nano. The Ultrasonic sensor is mounted perpendicular to the ground and accurately engages between 0.04m and 0.60m distances. The barometer is used to determine altitude beyond the ultrasonic range. The accelerometer and gyroscope are used to detect changes in pitch and roll, so that overall orientation can be determined. The servos would similarly be used to correct or cause changes in roll/pitch for the semi-autonomous landing.



Figure 5 (Circuit Diagram)





Figure 6 (Electronics Block Diagram)


Design Constraints and Limitations
	During development of the ROM-623 obstacles that were not accounted for resulted in the omission of some design goals. Primarily all group members, save one, were mandatorily deregistered from the course and subsequently left the project. This resulted in scheued timelines, and unmanageable workloads. This obstacle ultimately forced the development team to abandon the first person view implementation, as well as the transceiver/wireless communication. The mass of the ROM-623 exceeded 250g because of changes to: adhesive, a propeller mount, wiring, prototype board, breadboard, and galvanized wire. The masses of these elements were difficult to account for, however with further time investments it would be possible to reduce the overall mass further.  

Software Breakdown

Concept Designs
This subsection reviews the development of the system’s method of operation in terms of the scheduler. The final scheduling method was the Preemptive method; chosen due to its feasibility with dynamic and large scope applications. 

Cooperative
The cooperative scheduler is a method of scheduling tasks which can communicate back to the scheduler implementing smart scheduling. CoOperative schedulers are commonly used in the embedded systems industry as embedded systems are usually extremely isolated and perform a static or at least deterministic set of tasks. Having controlled tasks implemented by developers following a single standard allows for more flexible development as less failsafes have to be implemented due to the specific and heavily followed development standards [13]. Tasks created for the CoOperative scheduler know their importance compared to all other tasks, as all possible tasks are known at the start of the system with the CoOperative model. With tasks knowing their importance they can communicate with the scheduler asking for more time to complete their set of instructions, or the alternative they can yield, in other words give back control, to the scheduler to execute another job. When a job yields the scheduler will start the next job in the schedule, after the new job completes or yields, if there is extra time or jobs of less priority or importance based on the applied algorithm the previous yielded jobs will be resumed. 
	The intended application of the ROM-623’s scheduler was to be multi-purpose in the sense of new jobs being created at runtime, and in future receiving new tasks definitions over the network at runtime. With this application the system is no longer isolated to the extent where tasks know their importance, therefore they can not accurately decide when to yield. A more impactful factor is that different developers may be creating the runtime tasks, which if they are evil, in the sense of not yielding when is optimal, the system may fail or miss an important deadline. These problems make the CoOperative scheduler unsuitable for the ROM-623’s intended application.

Preemptive
The Preemptive scheduler is a method of scheduling tasks where if the current task execution should stop or another one should start the scheduler can perform a context switch. Preemptive schedulers are commonly used in large open systems, such as common day operating systems. These systems are exposed to new tasks extremely often by developers or even users, creating new task definitions the scheduler has to work with. When the scheduler works with the new tasks it has to be told their importance or decide them for itself with the chosen algorithm. When the scheduler has started a job and the job needs to be halted or another job must be started the scheduler can not trust the running task to end or pause itself; to accomplish this halting requirement the scheduler performs a context switch, forcefully halting the running job and starting the next job. If the next job is completed or halted and there is extra time or no tasks with high importance with respect to the chosen algorithm the scheduler will resume the previous halted jobs [14].
Due to the schedulers requirement to handle new task definitions at runtime, it must be smart, in the sense that it has to add the new task to the existing schedule and decide or be told its importance compared to the other jobs. This complexity of the scheduler makes it more difficult to implement, as the implementation has to handle all future unknown tasks and situations without any special case exceptions. While this scheduling method results in a higher complexity then that of the alternative, the ROM-632’s application requires the runtime functionality of the Preemptive scheduling method; resulting in the Preemptive scheduler as the ROM-623’s scheduler implementation.

Detailed Analysis
	The source code for the ROM-623 is available at: https://github.com/Emmanuel-Aaron/rom-623

Tasks
Tasks are a block of information that can be broke into three sections, identification, execution constraints, and time information. These sections allow the scheduler to get information about the job with a fair level of abstraction. 
The identification is a value which is used to identify the task for the scheduler to relate jobs to the task definition and for dynamic operation.
The execution constraints dictate how the task will affect the running system, in terms of what resources the job will need or if there are any dependent jobs that must be completed prior to its execution. The execution constraints also inform the scheduler of if the job is interruptible in terms of a context switch, as hard deadline jobs are by default uninterruptible, and what the instructions are of the job, in other words what procedure(s) must the job execute to be considered complete.
The time information expresses the nature of the tasks desired execution timing and importance with respect to the chosen algorithm. The information in the time information section can be analysed in terms of 3 subsections, priority, timing, and deadline. The priority is the basic importance weighting of jobs in relation to others, in our standard the values range from 0 to 10, with 10 being the highest priority. The timing indicates the task’s period or if it's periodic at all, with the alternative being aperiodic or sporadic. Timing also consists of the release time, regarding when the task is first ready available to be executed, and the execution time, the extent of time required to complete a job from the beginning to end of execution. The deadline indicates when the task must be completed relative to the period, and the type of deadline, as in if the deadline is soft (can be missed without system failure) or hard/firm (if missed system failure). If the task is a hard deadline the scheduler will attempt to context switch to it to complete the task before its deadline. The implementation of the task in the C programming language is by the use of structs, the Task is a struct which contains an execution constraint and time information struct nested inside. The identification is a single value which could be generated by a uuid generator or manually assigned to the job. It is essential that each task possesses a unique identification value with respect to all the other tasks so the scheduler can identify it apart from the others.

Scheduler
	The scheduler is composed of 6 components which are the job schedule, dynamic job structure, instruction linkage, dynamic algorithm and feasibility, dispatcher, and hard deadline. 
The job schedule is a list of jobs in terms of the hyperperiod of all the jobs that are intended to be scheduled. The jobs are executed from the start to the end of the list then continous this cycle by starting again at the beginning of the list. The schedule is implemented as an array of task pointers, which point to tasks defined in a task array which stores all the currently known task definitions.
The dynamic jobs structure is a series of methods of which to add and remove jobs at runtime. The scheduler after the completed execution of every job checks a que for requests of jobs to be added, if a job exists in the que it is passed to the task definition list; after all the jobs in the que have been added to the task definition list (task def list) they are added in the schedule. The jobs added in the que are actual task definitions, referred to as task structures and are copied to the task def list. Once all the que has been fully traversed every element in the que is written to 0, to identify no task is in the que.
The instruction linkage is a way instructions can be referenced by jobs, this method is superior to having a static method defining instructions in the task itself as a task can now change its instructions. Instructions must be identified by a value and the jobs then reference this value indicating its the instruction it wants to execute. Job instructions are stored in an array of function pointers, this constrains the jobs to all have the same arguments and return type.
Dynamic algorithm is the component of the scheduler to which it can arrange the jobs in the schedule. A potential algorithm for the scheduler could be the earliest deadline first, which orders the jobs so the earliest deadline has the highest priority while still considering execution time and period. This algorithm would utilize the hyperperiod schedule to place multiple instances of jobs if required to build the schedule. Since the algorithm is dynamic the scheduler can change its algorithm at runtime which can be performed as a job. Similar to the instruction linkage the dynamic algorithms are implemented as function pointers permitting their dynamic implementation.
The feasibility is a check the scheduler can perform each time it intends to schedule new jobs in the schedule. This feasibility task assesses if the jobs can be scheduled, currently the only check performed is in terms of cpu utilization, which checks if the execution times of jobs are longer than that of their period. An example of this is if a job has a longer execution time then its period a new job will want to start before the previous job has finished, if a context switch was performed to switch to the new job an infinite train of context switches would occur and no job would ever finish. In our implementation their are exceptions to this method of checking feasibility. Due to many of the tasks being soft deadlines their deadline can be late, so if the deadlines were equal to their period the new job could be paused and the old job could be resumed it would allow completion of the jobs even if cpu utilization is above unity. Another alternative is if the jobs were started later then their period this would also allow execution of all the jobs. This is the reason for having a dynamic ability to check for feasibility as it would be different for each application.
The dispatcher handles the jobs after they have been executed, if a job is aperiodic after the job has been completed the dispatcher would remove the job from the schedule so it is not executed again.
Hard deadlines are a notifier for the scheduler to invoke a context switch. When the scheduler has started it looks for the next hard deadline job, if the job is a hard deadline, to complete it before its deadline it sets a clock driven interrupt with the jobs instruction linkage so the interrupt occurs at the required time so the job can finish execution before its deadline then resumes the old halted job. After each hard deadline job the next interrupt is set for the next hard deadline job. The interrupts are performed by writing to arduino registers telling the arduino to perform desired interrupt service routine (ISR) which executes a job's instructions when a compare value equals that of the timer. The timer counts up to a max value, between this value and zero a value can be selected for a compare value, if the timer equals that value it resets back to 0 and the ISR is performed. To prevent the ISR from constantly running at a fixed period a value of 0 is written to a register disabling the compare value in turn disabling the interrupt.


Flight Algorithms
	The flight algorithms are algorithms which read from the onboard sensors which are the ultrasonic, barometer, and accelerometer. The values of these sensors allow the algorithms to determine properties of the plane's flight such as the orientation, altitude, and redundant low level altitude. The reason for two altitude readings is the barometer, a sensor which measures pressure can be used to determine altitude, this has many underlying assumptions about fluid conditions that are out of the scope of this project to define. However in simple form this sensor has a large tolerance in that it could be meters off in value. This large tolerance creates a dilemma when attempting to land the aircraft. For the solution to this problem an ultrasonic sensor was used to measure short range distance which has much lower tolerance then the barometer allowing for more accurate readings at near ground altitudes. The flight algorithms can utilize the scheduler, so if an algorithm should only be applied in a specific condition it can create a new job for a new algorithm to be applied then delete itself. The current demonstration algorithms are pre autonomous landing and post autonomous landing. The autonomous landing feature is for when the plane is arriving close to the ground it attempts to land. For the simple example application the pre autonomous landing slows down the motor so that the plane lowers in altitude and tilts the ailerons so its pitch is steep and negative or towards the ground. After the altitude is reached the job when executed next spawns the new post autonomous landing jobs and kills or removes itself. The post autonomous landing job has a higher pitch then its pre autonomous counterpart but is still negative and maintains the motor at a constant speed. This allows the plane to come to a smooth landing. Both these algorithms tilt the ailarons so the plane corrects its roll to be 0, or in other words level to the ground with respect to roll.

Figure 7 (Software Block Diagram)


Design Constraints and Limitations
	The most obvious constraints to the development of the software on the ROM-623 was time. Due to the tight timeline creating a full marketable product is near impossible especially when it's extremely interdisciplinary and the information required to learn is very time demanding. 
A constraint regarding the flight operation was that rf communication was not able to be added to the plane. The plane was not meant to be fully autonomous, as an operator was meant to control the plane with a wireless remote until the landing procedure was triggered which would be fully autonomous. Due to the timeline and the importance of the autonomous landing to demonstrate the real-time and hard deadline components of the system the user operation was eliminated from the development plan entirely. This elimination caused testing of the plane's flight to be near impossible as getting the plane in the air now required an autonomous procedure, and getting the plane to a state where it could land from an in-flight state required a fully autonomous plane. Another constraint with the flight operation was the autonomous algorithms, abstractly these are quite simple to solve, however when you are not able to test these theorized algorithms without jeopardizing the entire aircraft because there is no user operating the algorithms become much harder to verify. 
Limitations with respect to sensors consist of the errors with the ultrasonic and barometric sensors. Due to the plane not reaching an idealized flight altitude the barometer almost never reads an accurate reading as its tolerance is larger than the plane's distance to the ground. The ultrasonic sensor uses sound waves to identify how far something is from the plane's wheel base. When the plane is level and in motion the sound waves are sent directly at the ground the shortest real distance from the plane. These sound waves bounce back to where the plane was when they were initially emitted which the plane is no longer located at, causing the sensor reading to not be recorded correctly. After the sound wave has reached the plane from the waves dispersing or bouncing off of objects the reading is then recorded, causing the sensor to produce an overestimated time of sound travel yielding an over estimated distance from the ground.
The current scheduling method after every job checks the que and other requirements, this check can be redundant if jobs are guaranteed to be static. In this scenario a scheduling method using frames would be more beneficial by only checking the queue after a specific time interval. If this algorithm was dynamic it would allow for a more general purpose scheduler and allow for more potential optimizations such as the frame scheduling technique.
The current method of adding and removing tasks is poorly designed as adding and removing tasks are performed completely differently. A better approach would be to use the que as a request system, where a request to change the scheduling algorithm could be made, or a request to remove a current job could be done. This again would allow for a more general purpose scheduler and permit further optimizations.


Potential Applications

Research
Scheduling Quantification would be an experiment in the sense of testing different scheduling algorithms for an application. An example for this would be an autonomous vehicle, such as an autonomous delivery vehicle. Most applications may run one algorithm straight bare metal, perhaps even on an Field Programmable Gate Array. However if separate algorithms wanted to be tested to see the benefits to the application, such as the frame optimization with the ROM-623 in the flight scenario where there are times with static jobs, an entire rewrite or software component would have to be swapped out. The application of the ROM-623’s scheduler is to be able to create all the algorithms and have a job swap the scheduling algorithm at runtime, this results in no rewight or repromming required while still fully obeying the desired algorithm.

A more complex research possibility could be a method of testing hierarchical structures in large communication networks. These networks are often immensely complex, and changes to the system would most likely not be possible without much time and effort spent rewriting software components. An example of where this could be applied is in a swarm system, which is where multiple units/systems or in common applications robots, communicate with each other to solve a common task. If there were four robots and one robot was the leader it would instruct the other robots to accomplish specific tasks. Some of these robots solving such tasks may work in groups and have a sub leadership. If the scenario arises where the leader robot died the whole system would collapse as no order would be supplied to the worker or sub leader robots. A solution to this is an implementation of a governing system, or algorithm. The issue with government algorithms is identifying holes in the system and testing other government algorithms in the same scenarios. A solution to this entire problem would be a design similar to the ROM-623’s dynamic scheduler. If all the algorithms for the governing system could be swapped out for an alternative system at runtime then multiple governing systems could be tested in the exact same scenarios and even environments.

Industry
	An industry application also involving swarm robotics would be autonomous vehicle/aircraft search and rescue missions. In search and rescue missions information is constantly changing, and some information may be weighted differently than others. The ROM-623’s scheduler design could be used to schedule time sections to devoting a specific time window on investigating a specific lead. This method could support leads being deleted, or even experiencing a weighting change as the ROM-623 has almost every part of its system dynamic and could handle the demanding updates of the search and rescue mission.

References
[1]	“Flightline F4U-1D Corsair ‘Bubble top’ ‘1600mm,’” Motion RC. [Online]. Available: https://www.motionrc.com/products/flightline-f4u-1d-corsair-bubble-top-1600mm-63-wingspan-pnp?variant=19840700940401https%3A%2F%2Fwww.toprcmodel-usa.com%2Ff4u-corsair.html. [Accessed: 09-Dec-2021].
[2]	“Hobbyzone F4U Corsair S RTF with Safe Technology,” RC Superstore. [Online]. Available: https://www.rcsuperstore.com/hobbyzone-f4u-corsair-s-rtf-with-safe-technology/. [Accessed: 09-Dec-2021].
[3]	“Hobby zone,” HOBBY ZONE. [Online]. Available: https://www.hobbyzone.com/rc-airplanes/corsair/. [Accessed: 09-Dec-2021].
[4]	“F4U-4 Corsair 1100mm PNP,” Arrows RC. [Online]. Available: https://www.arrowsrc.com/arrows_rc_planes/AH008P.html. [Accessed: 09-Dec-2021].
[5]	“Rhino 6000mah 4s 50c lipo battery pack W/XT90,” Hobbyking. [Online]. Available: https://hobbyking.com/en_us/rhino-6000mah-4s-50c-lipo-battery-pack-w-xt90.html?queryID=79fc7db7093ab42e6f1efa8320692a60&objectID=80887&indexName=hbk_live_products_analytics. [Accessed: 09-Dec-2021].
[6]	“Turnigy aerodrive SK3 - 6374-192KV brushless outrunner motor,” Hobbyking. [Online]. Available: https://hobbyking.com/en_us/turnigy-aerodrive-sk3-6374-192kv-brushless-outrunner-motor.html?queryID=9198df17697f230490f790e212eb3dc7&objectID=17322&indexName=hbk_live_products_analytics. [Accessed: 09-Dec-2021].
[7]	“Turnigy plush-32 100A (2~6s) brushless speed controller w/BEC (rev1.1.0),” Hobbyking. [Online]. Available: https://hobbyking.com/en_us/turnigy-plush-32-100a-2-6s-brushless-speed-controller-w-bec-rev1-1-0.html?queryID=ee0c56031bf4ce8c6b99d7e0f5023bcc&objectID=86266&indexName=hbk_live_products_analytics. [Accessed: 09-Dec-2021].
[8]	Is This The Outlaw Build Video. 2021. https://www.youtube.com/watch?v=MzTJpBjbMgI
[9]	“Turnigy aerodrive SK3 - 2822-1740kv brushless outrunner motor,” Hobbyking. [Online]. Available: https://hobbyking.com/en_us/turnigy-aerodrive-sk3-2822-1740kv-brushless-outrunner-motor.html. [Accessed: 09-Dec-2021].
[10]	“Hobbyking 20A (2~4s) ESC 3A UBEC,” Hobbyking. [Online]. Available: https://hobbyking.com/en_us/hobby-king-20a-esc-3a-ubec.html?___store=en_us. [Accessed: 09-Dec-2021].
[11]	“Rhino 500mah 2s 20c lipo battery pack W/XT30,” Hobbyking. [Online]. Available: https://hobbyking.com/en_us/rhino-500mah-2s-20c-lipo-battery-pack-w-xt30.html. [Accessed: 09-Dec-2021].
[12]	Mazz, “Clark Y airfoil Pros and Cons,” Thoracentesis, 24-Feb-2021. [Online]. Available: http://www.thoracentesis.science/2021/02/Clark-Y-airfoil%20.html. [Accessed: 09-Dec-2021]. 
[13]	B. Priambodo, “Cooperative vs. preemptive: A quest to maximize concurrency power,” Medium, 03-Sep-2019. [Online]. Available: https://medium.com/traveloka-engineering/cooperative-vs-preemptive-a-quest-to-maximize-concurrency-power-3b10c5a920fe. [Accessed: 09-Dec-2021]. 

[14]	“Preemptive and non-preemptive scheduling,” GeeksforGeeks, 25-Aug-2021. [Online]. Available: https://www.geeksforgeeks.org/preemptive-and-non-preemptive-scheduling/. [Accessed: 09-Dec-2021]. 
