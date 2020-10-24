from gql import gql, Client, AIOHTTPTransport
import json

graphql_url = "<placeholder>"
transport = AIOHTTPTransport(url=graphql_url)
client = Client(transport=transport, fetch_schema_from_transport=True)

add_result_mutation = gql(
    """
    mutation add_result_mutation(
        $communityName: String!
        $player1Name: String!
        $player2Name: String!
        $date: timestamptz!
        $player1Goals: Int!
        $player2Goals: Int!
        $extraTime: Boolean!
      ) {
        insert_results(
          objects: {
            community: {
              data: { name: $communityName }
              on_conflict: {
                constraint: communities_name_key
                update_columns: name
              }
            }
            date: $date
            player1: {
              data: {
                name: $player1Name
                community: {
                  data: { name: $communityName }
                  on_conflict: {
                    constraint: communities_name_key
                    update_columns: name
                  }
                }
              }
              on_conflict: {
                constraint: players_name_communityId_key
                update_columns: name
              }
            }
            player2: {
              data: {
                name: $player2Name
                community: {
                  data: { name: $communityName }
                  on_conflict: {
                    constraint: communities_name_key
                    update_columns: name
                  }
                }
              }
              on_conflict: {
                constraint: players_name_communityId_key
                update_columns: name
              }
            }
            player2goals: $player2Goals
            player1goals: $player1Goals
            extratime: $extraTime
          }
        ) {
          returning {
            id
          }
        }
      }
    """
)

if __name__ == '__main__':
    suffix_for_test = "__temp2"

    with open("backup.json", "r") as backup_file:
        results_to_restore = json.load(backup_file)

        single_result = filter(lambda r: r["community"]["name"] == "test4", results_to_restore["results"])

        print("Restoring...")
        for result in single_result:
            test_community_name = f'{result["community"]["name"]}{suffix_for_test}'
            params = {
                "communityName": test_community_name,
                "player1Name": result["player1"]["name"],
                "player2Name": result["player2"]["name"],
                "player1Goals": result["player1goals"],
                "player2Goals": result["player2goals"],
                "date": result["date"],
                "extraTime": result["extratime"]
            }
            print(test_community_name)
            print(
                f'{params["player1Name"]} {params["player1Goals"]}:{params["player2Goals"]} {params["player2Name"]} {params["date"]} {params["extraTime"]}')
            client.execute(add_result_mutation, variable_values=params)
        print("Restore completed")

