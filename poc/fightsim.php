<?php

class Roll
{
	private $die;

	private $num;
	private $mod;

	private $skill;

	public function __construct($n=3, $m=0)
	{
		$this->num = $n;
		$this->mod = $m;

		$this->skill = null;

		$this->die = array();
		for($i = 0; $i < $n; $i++)
		{
			$this->die[] = mt_rand(1, 6);
		}
	}

	public function set_skill($skill)
	{
		$this->skill = $skill;
	}

	public function get_rollmsg()
	{
		return "Rolled {$this->num}d+{$this->mod} and got ".implode(', ', $this->die)." for ".$this->get_result();
	}

	public function get_rolls()
	{
		return $this->die;
	}

	public function get_result()
	{
		return array_sum($this->die) + $this->mod;
	}

	public function get_degreeofsuccess()
	{
		if($this->test_skill())
		{
			return $this->skill - $this->get_result();
		} else {
			return null;
		}
	}

	public function test_skill()
	{
		if(is_null($this->skill))
		{
			return null;
		}
		//echo "Testing skill of {$this->skill} ";

		return $this->skill > $this->get_result();
	}
}

class Character
{
	private $max_str;
	private $max_dex;
	private $max_int;
	private $max_per;

	private $cur_str;
	private $cur_dex;
	private $cur_int;
	private $cur_per;

	private $weap_skill;
	private $shield_skill;

	private $armor = 0;
	private $shield = 0;

	private $ap = 0;

	private $last_defense = '';

	public function __construct($str, $dex, $int, $per, $weap_skill)
	{
		$this->max_str = $str;
		$this->max_dex = $dex;
		$this->max_int = $int;
		$this->max_per = $per;

		$this->cur_str = $str;
		$this->cur_dex = $dex;
		$this->cur_int = $int;
		$this->cur_per = $per;

		$this->weap_skill = $weap_skill;
	}

	public function get_attrs()
	{
		return array(
			$this->cur_str,
			$this->cur_dex,
			$this->cur_int,
			$this->cur_per
		);
	}

	public function get_speed()
	{
		return $this->cur_dex/2 + $this->cur_str/4 + $this->cur_per/4;
	}

	public function get_dodge()
	{
		return $this->get_speed() + $this->shield;
	}

	public function get_parry()
	{
		return $this->get_weap_skill() / 2 + 3 + $this->shield;
	}

	public function get_block()
	{
		if($this->shield > 0)
		{
			return $this->get_stat_modifier($this->cur_dex, $this->max_dex) * $this->shield_skill + $this->shield;
		} else {
			return 0;
		}
	}

	public function get_weap_skill()
	{
		return $this->get_stat_modifier($this->cur_str, $this->max_str) * $this->weap_skill;
	}

	public function get_stat_modifier($current, $max)
	{
		return 0.5 + 0.5 * ($current / $max);
	}

	public function get_defense_label()
	{
		return $this->last_defense;
	}

	public function set_shield($shield_value, $shield_skill)
	{
		$this->shield = $shield_value;
		$this->shield_skill = $shield_skill;
	}

	public function set_armor($armor)
	{
		$this->armor = $armor;
	}

	public function tick()
	{
		$this->ap += $this->get_speed();
		return $this->ap > 0;
	}

	public function take_step()
	{
		$this->ap -= 110 - $this->get_speed();
	}

	public function take_swing($weap_weight, $dmg_mod = 0)
	{
		$this->ap -= 100 + 100 * $weap_weight * $weap_weight / $this->cur_str - $this->get_speed();

		$roll = new Roll();
		$roll->set_skill($this->get_weap_skill());
		$result = $roll->test_skill();
		if($result)
		{
			$eff_str = $this->cur_str + floor($roll->get_degreeofsuccess() / 3);
			if($eff_str >= 9)
			{
				$n = floor( ($eff_str - 9)/4 ) + 1;
				$m = ($eff_str - 9)%4 - 1;
			} else {
				$n = 1;
				$m = 6 - floor( $eff_str/2 );
			}

			$dmg = new Roll($n, $m+$dmg_mod);
			return max(1, $dmg->get_result());
		} else {
			return 0;
		}
	}

	public function defend()
	{
		$dodge = $this->get_dodge();
		$parry = $this->get_parry();
		$block = $this->get_block();

		if($dodge > $parry && $dodge > $block)
		{
			$def = $dodge;
			$label = "dodged";
		} elseif($parry > $block) {
			$def = $parry;
			$label = "parried";
		} else {
			$def = $block;
			$label = "blocked";
		}

		$this->last_defense = $label;

		$roll = new Roll();
		$roll->set_skill($def);
		return $roll->test_skill();
	}

	public function take_damage($dmg)
	{
		$split = mt_rand() / mt_getrandmax();
		$dmg = max(0, $dmg - $this->armor);
		$str_dmg = floor($split * $dmg);
		$dex_dmg = floor((1-$split) * $dmg);

		$this->cur_str -= $str_dmg;
		$this->cur_dex -= $dex_dmg;

		//echo "{$dmg} points of damage split between {$str_dmg} and {$dex_dmg} ";
	}

	public function is_alive()
	{
		return
			$this->cur_str > 0 &&
			$this->cur_dex > 0 &&
			$this->cur_int > 0 &&
			$this->cur_per > 0;
	}
}

$MAX_DUELS = 500;
$stats = array();
//$firstbloodvictor = 0;
for($kobolds = 1; $kobolds <= 5; $kobolds++)
{
	$stats[$kobolds]['Kobolds'] = $kobolds;
	$stats[$kobolds]['Hero Wins'] = 0;
	$stats[$kobolds]['Kobold Wins'] = 0;

	echo "Starting {$MAX_DUELS} duels with {$kobolds} kobolds\n";

	for($duel = 0; $duel < $MAX_DUELS; $duel++)
	{
		$kobolds_alive = 0;
		$hero = new Character(13, 12, 12, 10, 13);
		//$hero->set_shield(1, 11);
		$hero->set_armor(3);
		$actors = array(
			array("name"=>"Hero", "is_pc"=>true, "char"=>$hero, "weapon"=>array(2,2))
		);
		for($k = 0; $k < $kobolds; $k++)
		{
			$kobold = new Character(9, 10, 10, 10, 10);
			$actors[] = array("name"=>"Kobold ".($i+1), "is_pc"=>false, "char"=>$kobold, "weapon"=>array(1,1));
			$kobolds_alive++;
		}
		//$fight_stats = array(
		//	"Duel"=>$duel+1,
		//	"Ticks"=>0,
		//	"First Blood"=>null,
		//	"Victor"=>null,
		//	"Hero Hits"=>0,
		//	"Hero Dodges"=>0,
		//	"Kobold Hits"=>0,
		//	"Kobold Dodges"=>0
		//);

		echo "\tStarting duel...";
		while($actors[0]['char']->is_alive() && $kobolds_alive > 0)
		{
			//$fight_stats["Ticks"]++;
			foreach($actors as $actor)
			{
				if(!$actor['char']->is_alive())
				{
					continue;
				}

				if($actor['char']->tick())
				{
					$lastactor = $actor['name'];
					//echo "{$actor['name']} takes a swing! ";
					$dmg = $actor['char']->take_swing($actor['weapon'][0], $actor['weapon'][1]);
					if($dmg > 0)
					{
						//Apply damage to the first non-dead non-teammate actor
						for($i = 0; $i < count($actors); $i++)
						{
							//echo "Checking actor {$i} as valid target...";
							if($actors[$i]['is_pc'] == $actor['is_pc'])
							{
								//echo "Not valid target because same team";
								continue;
							} elseif(!$actors[$i]['char']->is_alive()) {
								//echo "Not valid target because dead";
								continue;
							}
							//echo " Actor {$i} takes {$dmg} damage!";

							if($actors[$i]['char']->defend())
							{
								//echo "{$actors[$i]['name']} dodges the attack!\n";
								//$fight_stats["{$actors[$i]['name']} Dodges"]++;
							} else {
								$actors[$i]['char']->take_damage($dmg);
								//echo "{$actors[$i]['name']} is reduced to [".implode(', ', $actors[$i]['char']->get_attrs())."]\n";

								if($actors[$i]['is_pc'] == false && $actors[$i]['char']->is_alive() == false)
								{
									$kobolds_alive--;
								}
							}

							$dmg = 0;
						}
					} else {
						//echo "It's a miss! ";
					}
					//echo "\n";
				}
			}
		}

		echo " Duel over! Winner: ";
		//$stats[] = $fight_stats;
		if($actors[0]['char']->is_alive())
		{
			$stats[$kobolds]['Hero Wins']++;
			echo "Hero!\n";
		} else {
			$stats[$kobolds]['Kobold Wins']++;
			echo "Kobolds!\n";
		}
		//echo "\n";
	}
}

//Now we'll print out the stats
echo implode(',', array_keys($stats[1]))."\n";
foreach($stats as $stat)
{
	echo implode(',', $stat)."\n";
}
//echo "First Blood Is Victor,{$firstbloodvictor},".round(100*$firstbloodvictor/$MAX_DUELS, 2)."%\n";

