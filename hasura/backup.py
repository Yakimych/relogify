from gql import gql, Client, AIOHTTPTransport
import json

graphql_url = "<placeholder>"
transport = AIOHTTPTransport(url=graphql_url)
client = Client(transport=transport, fetch_schema_from_transport=True)

all_results_query = gql(
    """
    query all_results {
          results {
            player1 {name}
            player2 {name}
            player1goals
            player2goals
            extratime
            date
            community {name}
        }
    }
    """
)

if __name__ == '__main__':
    all_results_json = client.execute(all_results_query)
    with open("backup.json", "w") as backup_file:
        json.dump(all_results_json, backup_file)

