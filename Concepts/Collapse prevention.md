# Collapse prevention

A collapse is when the panel voltage breaks down because more power is required, than the panel can provide.
The overall power after the collapse is strongly reduced and the only way to restore the maximum power is to reduce the demand even more until the voltage increases again.

There are several unfavourable conditions that can lead to a collapse:  
- Partial shading,
- Scatterd clouds with winds, leading to alternating full power/reduced power phases,
- Dawn/dusk when the steady changes in power from the rising/falling sun can fool the MPPT algorithm into believing the changes were due to its own changes of maximum power point.

Collapses frequently repeat as themselves into oscillations, dramatically reducing the overall power harvesting. 
That happens also with commercial systems, the situation mainly remains unnoticed from the user, because it is a transitory situation. 

Soft power2 MPPT is implementing a collapse prevention mechanism, to avoid that unfavourable situation.

![image](https://user-images.githubusercontent.com/14197155/123589381-6a8e6200-d7e9-11eb-97c1-d48f40c7f9e3.png)
